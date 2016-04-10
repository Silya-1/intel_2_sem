#ifndef __FILE_H__
#define __FILE_H__
#include <stdio.h>
#include <string.h>
#define size 20
class CFILE
{
private:
    FILE *file;
public:
    CFILE(char * name, char* do_file);
    ~CFILE();
    char get_symbol();
    char* get_str(char *s);
    void file_out(char *s);
};
char* CFILE::get_str(char *s)
{
    //char s[size];
    fscanf(file, "%20s", s);
    get_symbol();
    return s;
}
CFILE::CFILE(char * name, char* do_file)
{
    file = fopen(name, do_file);
}
CFILE::~CFILE()
{
    fclose(file);
}
char CFILE::get_symbol()
{
    char c;
    c = getc(file);
    return c;
}
void CFILE::file_out(char *s)
{
    fprintf(file, " %s ", s);
}
#endif
