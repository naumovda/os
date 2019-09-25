#include <stdio.h>

int main (void)
{
	FILE *in, *out;

	struct pirate {
		char name[100]; /* настоящее имя */
		unsigned long booty; /* вознаграждение в фунтах стерлингов */
		unsigned int beard_len; /* длина бороды в дюймах */
	} p, blackbeard= { "EdwardTeach", 950, 48 };

	out = fopen ("data", "w");
	if (!out) {
		perror ("fopen");
		return 1;
	}

	if (!fwrite (&blackbeard, sizeof (struct pirate), 1, out)) {
		perror ("fwrite");
		return 1;
	}
	
	if (fclose (out)) {
		perror ("fclose");
		return 1;
	}
	
	in = fopen ("data", "r");
	if (!in) {
		perror ("fopen");
		return 1;
	}
	
	if (!fread (&p, sizeof (struct pirate), 1, in)) {
		perror ("fread");
		return 1;
	}
	
	if (fclose (in)) {
		perror ("fclose");
		return 1;
	}

	printf ("name=\"%s\" booty=%lu beard_len=%u\n",
			p.name, p.booty, p.beard_len);

	return 0;
}