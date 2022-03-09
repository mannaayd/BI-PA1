#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct                                                                                          // struct for phrases
{
    double f;                                                                                           // frequency
    char *sentence;                                                                                     // phrase
}phrase;

phrase *phrases;                                                                                        // pointer to array of phrases

int compare(const void* a, const void* b)                                                               // compare function for qsort
{
    phrase *a1 = (phrase*)a;
    phrase *a2 = (phrase*)b;
    if ((double)a1->f < (double)a2->f) return 1;
    if ((double)a1->f > (double)a2->f) return -1;
    return 0;
}

int error(int count)                                                                                    // function for print "Invalid input data" message and free memory
{
    printf("Nespravny vstup.\n");
    for(int i = 0; i < count; i++)
    {
        free(phrases[i].sentence);
    }
    free(phrases);
    return 1;
}


int readInputPhrases(int *count)                                                                        // function for read first part of input(phrases and frequency of this phrases) data 
{
    int first_char;                                                                                     // variable for sscanf to read number of first char int phrase
    int c;                                                                                              // helpful variable for counter
    size_t memsize = 0;                                                                                 // variable for getline to allocate memory
    char *line = NULL;                                                                                  // pointer to line for getline
    char ch;                                                                                            // char for sscanf to control data
    while(1)
    {
        if(getline(&line, &memsize, stdin) == -1) 
        {
            free(line);
            return error(*count);
        }
        if((int)strlen(line) == 1 && line[0] == '\n') break;
        (*count)++;
        phrases = (phrase*)realloc(phrases, (*count) * sizeof(phrase));
        phrases[(*count) - 1].sentence = NULL;
        if(sscanf(line, " %lf %c %n", &phrases[(*count) - 1].f, &ch, &first_char) != 2)
        {
            free(line);
            return error(*count);
        }                                                                                               
        if((int)strlen(line) == first_char || ch != ':' || phrases[(*count) - 1].f <= 0) 
        {
            free(line);
            return error(*count);
        }
        phrases[(*count) - 1].sentence = (char*)malloc(((int)strlen(line) - first_char) * sizeof(char));
        c = 0;
        for(int i = first_char; i < (int)strlen(line); i++)
        {
            phrases[(*count) - 1].sentence[c] = line[i];
            c++;
        }
        phrases[(*count) - 1].sentence[c - 1] = '\0';
    }
    free(line);
    return 0;
}

void findPhrase(int *count)                                                                             // function for finding phrases in text                                                   
{
    size_t memsize = 0;                                                                                 // variable for getline to allocate memory
    char *line = NULL;                                                                                  // pointer to text
    char ch;                                                                                            // variable for change for transform letter in lower case
    int *list = NULL;                                                                                   // pointer for indexes of find phrases
    int count_l = 0;                                                                                    // variable for count of find frases in text
    int flag = 0;                                                                                       // flag for exit from main cycle
    int flag_l;                                                                                         // flag for exit from finding cycle
    int tmp;                                                                                            // temporary variable for moving in lines
    printf("Hledani:\n");
    while(flag != -1)                                                                                   // main cycle
    {
        count_l = 0;
        flag = getline(&line, &memsize, stdin);                                                         // getting text to find phrases in
        line[(int)strlen(line) - 1] = '\0';
        
        for(int i = 0; i < *count; i++)                                                                 // finding cycle
        {
            flag_l = 0;
            for(int c = 0; c < (int)strlen(phrases[i].sentence); c++)
            {
                tmp = c;
                for(int r = 0; r < (int)strlen(line); r++)
                {
                    line[r] = (int)line[r] >= 'A' && (int)line[r] <= 'Z' ? (int)line[r] - 'A' + 'a' : (int)line[r];
                    ch = (int)phrases[i].sentence[tmp] >= 'A' && (int)phrases[i].sentence[tmp] <= 'Z' ? (int)phrases[i].sentence[tmp] + 'a' - 'A' : (int)phrases[i].sentence[tmp];
                    if(ch != (int)line[r] || phrases[i].sentence[tmp] == '\0') break;
                    if(r == (int)strlen(line) - 1)
                    {
                        count_l++;
                        list = (int*)realloc(list, count_l * sizeof(int));
                        list[count_l - 1] = i;
                        flag_l = 1;
                        break;
                    }
                    tmp++;
                }
                if(flag_l) break;
            }
        }
        if(flag != -1)                                                                                  // print information
        {
            printf("Nalezeno: %d\n", count_l);
            for(int i = 0; i < count_l; i++)
            {
                if(i == 50) break;
                printf("> ");
                printf("%s\n", phrases[list[i]].sentence);
            }
        }
    }
    free(list);
    free(line);
}

int main()                                                                                              
{
    phrases = (phrase*)malloc(sizeof(phrase));                      
    phrases[0].sentence = NULL;
    int count_ph = 0;                                                                                   // count of phrases                           
    printf("Casto hledane fraze:\n");
    if (readInputPhrases(&count_ph)) return 0;                                                          // read phrases
    if(count_ph <= 0) return error(1);
    qsort (phrases, count_ph, sizeof(phrase), compare);                                                 // sorting phrases by frequency
    findPhrase(&count_ph);                                                                              // find phrases in text
    for(int i = 0; i < count_ph; i++)                                                                   // free memory
    {
        free(phrases[i].sentence);
    }
    free(phrases);
    return 0;
}