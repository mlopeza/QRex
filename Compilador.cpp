#include "stdio.h"
#include "Parser.h"
#include "Scanner.h"
#include <sys/timeb.h>
#include <wchar.h>

using namespace QRex;

int main (int argc, char *argv[]) {
    
    if (argc == 2) {

        wchar_t *fileName = coco_string_create(argv[1]);
        QRex::Scanner *scanner = new QRex::Scanner(fileName);
        QRex::Parser *parser = new QRex::Parser(scanner);
        parser->Parse();
        if (parser->errors->count == 0) {
            printf("Analisis exitoso\n");
        }
        else {
            printf("Error\n");
        }

        coco_string_delete(fileName);
        delete parser;
        delete scanner;

    } else
        printf("-- No source file specified\n");

    return 0;
}
