/*================================== ABOUT ==================================\*

Input file parser. Written mostly using ChatGPT.

I need to add Boundary conditions parser with fictitious "0" node.

\*===========================================================================*/


#include "parser.h"
// #include "helper.h"

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void removeExcess(char* line) {
    char* comment = strchr(line, '#');
    if (comment) *comment = '\0';

    char* start = line;
    while (isspace((unsigned char)*start)) start++;

    char* end = start + strlen(start) - 1;
    while (end >= start && isspace((unsigned char)*end)) {
        *end = '\0';
        end--;
    }

    if (start != line) memmove(line, start, strlen(start) + 1);
}

LagrangeData parsePoints(FILE* file) {
    int lineSize = 1024;
    int pointsSize = 16;
    char line[lineSize];
    int count = 0;
    double** points = malloc(pointsSize * sizeof(double*));

    long lastPosition = ftell(file);

    while (fgets(line, sizeof(line), file)) {
        removeExcess(line);
        if (line[0] != '[') {
            fseek(file, lastPosition, SEEK_SET);
            break;
        }

        lastPosition = ftell(file);

        char* ptr = line;
        double x, y;
        int n;

        while (*ptr) {
            // Try to parse a point; tolerate optional spaces and optional comma
            if (sscanf(ptr, " [%lf , %lf ]%n", &x, &y, &n) == 2) {
                if (count >= pointsSize) {
                    pointsSize *= 2;
                    points = realloc(points, pointsSize * sizeof(double*));
                }
                points[count] = malloc(2 * sizeof(double));
                points[count][0] = x;
                points[count][1] = y;
                count++;

                ptr += n;

                // Skip optional comma and whitespace after the point
                while (*ptr == ',' || isspace(*ptr)) ptr++;
            } else {
                break;
            }
        }

        if (line[strlen(line) - 1] != ',') break;
    }

    return fillLagrangeData(points, count);
}


Link parseLink(char* line, FILE* file) {
    Link l = {0};
    char* nodesString;

    char* delimiter = strchr(line, ':');
    if (!delimiter) {
        printf("ERROR: Missing colon (:) in link syntax.\n");
        exit(EXIT_FAILURE);
    } else {
        *delimiter = '\0';
        l.name = strdup(line);
        nodesString = delimiter + 1;
    }

    delimiter = strstr(nodesString, "->");
    if (!delimiter) {
        printf("ERROR: Missing node delimiter (->) in link syntax.\n");
        exit(EXIT_FAILURE);
    } else {
        *delimiter = '\0';
        char* node1str = nodesString;
        char* node2str = delimiter + 2;
        removeExcess(node1str);
        removeExcess(node2str);
        l.inletNode = atoi(node1str);
        l.outletNode = atoi(node2str);
    }

    l.lData = parsePoints(file);
    return l;
}

LinkArray realLinksParser() {
    LinkArray x;

    FILE *file = fopen("inputs", "r");
    if (file == NULL) {
        perror("Error opening file");
        return x;
    }

    char line[1024];
    int capacity = 2;
    int count = 0;
    Link* links = malloc(capacity * sizeof(Link));

    int inLinksSection = 0;

    while (fgets(line, sizeof(line), file)) {
        removeExcess(line);
        if (strlen(line) == 0) continue;

        if (!inLinksSection) {
            if (strcmp(line, "LINKS") == 0) {
                inLinksSection = 1;
            }
            continue;
        }

        if (strcmp(line, "NODE CONDITIONS") == 0) {
            break;
        }

        if (count >= capacity) {
            capacity *= 2;
            links = realloc(links, capacity * sizeof(Link));
        }

        links[count++] = parseLink(line, file);
    }

    fclose(file);

    x.data = links;
    x.size = count;
    return x;
}
