#include <stdio.h>
#include <string.h>
#include <stdlib.h>

float solvebrac(int symb);
float readnum(void);
float calculate(float ans, int sym, float num);
void readword(void);
void setvar(void);

struct var{
    char name[17];
    float value; 
};
typedef struct var var;

int let = 0, num_count = 0, varcount = 0;
int found = 0;
float calc = 0;
char word[17];
var *storage;

int main(void)      
{ 
    storage = (var*)calloc(1,sizeof(var));
    //
    // strcpy(storage[0].name,"abc");
    // storage[0].value = 10;
    // varcount = 1;
    //
    if(storage == NULL)
    {
        printf("memory allocation failed\n");
        return 1;
    }
    while(1)
    {
        getchar();
        let = getchar();
        if((let == '+') || (let == '-') || (let == '*') || (let == '/'))
        {
            calc = solvebrac(let);
            printf("ANS = %.3f\n", calc);
        }
        else if(('a' <= let) && (let <= 'z'))
        {
            readword();
            if(strcmp(word,"set") == 0)
            {
                setvar();
            }
        }
        getchar(); // to get rid of the EOF
    }
}

float solvebrac(int symb)
{
    float result;
    num_count = 1;
    let = getchar();

    if((symb == '+') || (symb == '-')) result = 0;
    else if ((symb == '*') || (symb == '/')) result = 1;

    while(let != ')')
    {
        result = calculate(result, symb, readnum());
    }

    return result;
}

float readnum(void)
{
    float total = 0;
    let = getchar();

    if(let == '(')
    {
        let = getchar();
        total = solvebrac(let);
        let = getchar();
    }
    else if(('a' <= let) && (let <= 'z'))
    {
        found = 0;
        readword();
        for(int i = 0; i < varcount; i++)
        {
            if(strcmp(word, storage[i].name) == 0)
            {
                total = storage[i].value;
                found = 1;
                return total;
            }
        }
        if(found == 0)
        {
            printf("undefined variable\n");
            return 0;
        }
    }
    else
    {
        while((let != ' ') && (let != ')'))
        {
            total = total*10 + (let - '0');
            let = getchar();
        }
    }

    return total;
}

void readword(void)
{
    int i = 1;
    word[0] = let;
    let = getchar();
    while((let != ' ') && (let != ')'))
    {
        word[i] = let;
        let = getchar();
        i++;
    }
    word[i] = '\0';
}

void setvar(void)
{
    let = getchar();
    readword();

    for(int i = 0; i < varcount; i++)
    {
        if(strcmp(storage[i].name, word) == 0)
        {
            storage[i].value = readnum();
            return;
        }
    }
    strcpy(storage[varcount].name, word);
    storage[varcount].value = readnum();

    varcount++;

    storage = realloc(storage, (varcount+1) * sizeof(var));
}

float calculate(float ans, int sym, float num)
{
    if(sym == '+')
    {
        ans += num;
    }
    else if(sym == '-')
    {
        if(num_count == 1)
        {
            ans = num;
            num_count = 0;
        }
        else ans -= num;
    }
    else if(sym == '*')
    {
        ans *= num;
    }
    else if(sym == '/')
    {
        ans /= num;
    }

    return ans;
}