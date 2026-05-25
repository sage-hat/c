/*
* Program:    res.c
* Author:     sage
* Created:    22.05.2026
* Modified:   22.05.2026
* Version:    1.0
* Description: res - Convert resistor color bands
*         (4-band) to resistance value and tolerance
*
* Comments:    
*/
#include "run.h"
#include <locale.h>
#include <libintl.h>

#define LOCALEBASEDIR "."
#define TEXTDOMAIN "res"

int main(int argc, char **argv)
{
    setlocale(LC_CTYPE, "");
    setlocale(LC_MESSAGES, "");
    bindtextdomain(TEXTDOMAIN, LOCALEBASEDIR);
    textdomain(TEXTDOMAIN);
    main_process(argc, argv);
    return 0;
}
