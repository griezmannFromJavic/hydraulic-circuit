/*================================== ABOUT ==================================\*

Input file detect

Need to implemet function that is looking for repeated x values of lagrange polynomials

\*===========================================================================*/


#include "parser.h"
#include "helper.h"

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void removeExcess(char* line) {
    //removes comments, leading and trailing spaces.
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
        l.type = 'r'; //
    }

    l.lData = parsePoints(file);
    return l;
}

LinkArray realGraphParser(char* input) {
    LinkArray x;
    x.data = NULL;
    x.size = 0;

    FILE *file = fopen(input, "r");
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

    x.data = realloc(links, count * sizeof(Link));
    x.size = count;
    return x;
}


BoundaryCondition* boundaryParser(int* count) {
    FILE* file = fopen("inputs", "r");
    if (!file) {
        perror("Error opening inputs file");
        exit(EXIT_FAILURE);
    }

    char line[1024];
    int capacity = 8;
    int size = 0;
    BoundaryCondition* list = malloc(capacity * sizeof(BoundaryCondition));
    if (!list) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    int inSection = 0;
    while (fgets(line, sizeof(line), file)) {
        removeExcess(line);
        if (strlen(line) == 0) continue;

        if (!inSection) {
            if (strcmp(line, "NODE CONDITIONS") == 0) {
                inSection = 1;
            }
            continue;
        }

        char type;
        int node;
        double value;
        if (sscanf(line, "%c(%d) = %lf", &type, &node, &value) == 3) {
            if (type != 'p' && type != 's') {
                fprintf(stderr, "ERROR: Invalid boundary condition type '%c'\n", type);
                exit(EXIT_FAILURE);
            }

            int conflictType = 0;
            for (int i = 0; i < size; ++i) {
                if (list[i].node == node) {
                    if (list[i].type == type) {
                        // Same type and node = error
                        fprintf(stderr,
                            "ERROR: Duplicate boundary condition %c(%d)\n", type, node);
                        exit(EXIT_FAILURE);
                    } else {
                        // Same node, different type = warning
                        conflictType = 1;
                    }
                }
            }

            if (conflictType) {
                fprintf(stderr,
                    "WARNING: Both P(%d) and S(%d) are defined. This may overconstrain the node.\n",
                    node, node);
            }

            if (size >= capacity) {
                capacity *= 2;
                list = realloc(list, capacity * sizeof(BoundaryCondition));
                if (!list) {
                    perror("realloc failed");
                    exit(EXIT_FAILURE);
                }
            }

            list[size++] = (BoundaryCondition){node, type, value};
        } else {
            fprintf(stderr, "ERROR: Invalid boundary condition line: '%s'\n", line);
            exit(EXIT_FAILURE);
        }
    }

    fclose(file);
    *count = size;
    return list;
}
