#include "nemu.h"
#include "cpu/reg.h"
#include "memory/memory.h"

#include <stdlib.h>

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>

enum
{
	NOTYPE = 256,
	EQ,
	NUM,
	REG,
	SYMB,
	//
	HEX,
	/* TODO: Add more token types */

};

static struct rule
{
	char *regex;
	int token_type;
} rules[] = {

	/* TODO: Add more rules.
	 * Pay attention to the precedence level of different rules.
	 */

	{" +", NOTYPE}, // white space
	{"\\+", '+'},
	//
	{"[0-9]{1,10}", NUM}, //dec
	{"-", '-'},
	{"+", '+'},
	{"*", '*'},
	{"/", '/'},

	{"\\*", '*'},
	{"\\(", '('},
	{"\\)", ')'}
	{"\\-", '-'},
	{"\\/", '/'},
	//
	{"==", EQ},
	{"0[xX][0-9a-fA-F]+", HEX},
	



};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]))

static regex_t re[NR_REGEX];

/* Rules are used for more times.
 * Therefore we compile them only once before any usage.
 */
void init_regex()
{
	int i;
	char error_msg[128];
	int ret;

	for (i = 0; i < NR_REGEX; i++)
	{
		ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
		if (ret != 0)
		{
			regerror(ret, &re[i], error_msg, 128);
			assert(ret != 0);
		}
	}
}

typedef struct token
{
	int type;
	char str[32];
} Token;

Token tokens[32];
int nr_token;

static bool make_token(char *e)
{
	int position = 0;
	int i;
	regmatch_t pmatch;

	nr_token = 0;

	while (e[position] != '\0')
	{
		/* Try all rules one by one. */
		for (i = 0; i < NR_REGEX; i++)
		{
			if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0)
			{
				char *substr_start = e + position;
				int substr_len = pmatch.rm_eo;

				printf("match regex[%d] at position %d with len %d: %.*s", i, position, substr_len, substr_len, substr_start);
				position += substr_len;

				/* TODO: Now a new token is recognized with rules[i]. 
				 * Add codes to perform some actions with this token.
				 */

				switch (rules[i].token_type)
				{

				default:
					tokens[nr_token].type = rules[i].token_type;
					nr_token++;
				}

				break;
			}
		}

		if (i == NR_REGEX)
		{
			printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
			return false;
		}
	}

	return true;
}

//s:当前待求值表达式在tokens[]数组中的起始位置
//e:当前待求值表达式在tokens[]数组中的结束位置
uint32_t eval(int s, int e, bool *success)
{
	if(s>e)
	{
		/*Bad expression*/
		*success=false;
		return 0;
	}
	else if(s==e)
	{
		/* Single token.
		* For now this token should be a number. 
		* Return the value of the number.
		*/
		return eval(s+1,e-1);
	}
	else if(check_parentheses(s,e)==true)
	{
		
		return eval(s+1,e-1);
	}
	else
	{
		
	}
	
}

uint32_t expr(char *e, bool *success)/////////
{
	if (!make_token(e))
	{
		*success = false;
		return 0;
	}

	for(uint32_t i=0;i<nr_token;i++)
	{
		if(tokens[i].type=='*' && (i==0||tokens[i-1].type==))
	}





























	// printf("\nPlease implement expr at expr.c\n");
	// assert(0);

	// return 0;
}
