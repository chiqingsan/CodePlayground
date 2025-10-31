#ifndef FILE_UTILS_H
#define FILE_UTILS_H

void saveStudentsToFile(struct studentModel students[], int length, const char *filename);
void loadStudentsFromFile(struct studentModel students[], int length, const char *filename);

#endif
