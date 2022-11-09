#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

struct _osoba;
typedef struct _osoba* position;
struct _osoba
{
	char ime[20];
	char prezime[20];
	int godina;
	position next;

};
typedef struct _osoba osoba;
void insertFront(position);
void insertBack(position);
position findElement(position);
void printList(position);
void deleteElement(position);
void InsertPrev(position);
void Insert(position);
position FindPrez(position);
void InsertBefore(position);
position FindPrevPrez(position);
void SortList(position);
void PrintListToFile(position);
void ReadListFromFile(position);

int main()
{
	int broj = 0;
	osoba head;
	head.next = NULL;
	printf("izaberite jednu od mogucnosti \n");
	printf("1. dodavanje elementa na pocetak liste\n");
	printf("2. dodavanje elementa na kraj liste\n");
	printf("3. pronalazak elementa liste\n");
	printf("4. ispis liste\n");
	printf("5. brisanje elementa liste\n");
	printf("6. dodaj novi element iza odredenog elementa\n");
	printf("7. dodaj novi element prije odredenog elementa\n");
	printf("8. sortiraj listu po prezimenima\n");
	printf("9. upisi listu u datoteku\n");
	printf("10. citanje liste iz datoteke\n");
	printf("11. izlaz\n");

	scanf("%d", &broj);

	switch (broj)
	{
	case 1:
		insertFront(&head);
		break;
	case 2:
		insertBack(&head);
		break;
	case 3:
		findElement(head.next);
		break;
	case 4:
		printList(head.next);
		break;
	case 5:
		deleteElement(&head);
		break;
	case 6:
		InsertPrev(&head);
		break;
	case 7:
		InsertBefore(&head);
		break;
	case 8:
		SortList(&head);
		break;
	case 9:
		PrintListToFile(&head);
		break;
	case 10:
		ReadListFromFile(&head);
		break;
	case 11:
		break;
	default:
		printf("krivi unos");
		break;
	}

	return 0;
}

//prva fja
void insertFront(position head) {
	position q;
	q = (position)malloc(sizeof(osoba));
	if (q == NULL) {
		printf("Greska\n");
	}
	else {
		printf("Unesite ime, prezime i godinu rodenja studenta :\n");
		scanf_s(" %s %s %d", q->ime, 20, q->prezime, 20, &q->godina);
		q->next = NULL;
		q->next = head->next;
		head->next = q;
	}

}

//druga fja
void insertBack(position previous) {
	position q;
	q = (position)malloc(sizeof(osoba));
	if (q == NULL) {
		printf("Greska");
	}
	while (previous->next != NULL) {
		previous = previous->next;
		//q->next = previous->next;
		previous->next = q;

	}

}


//treca fja 
position findElement(position p) {
	char prezime[20] = { 0 };
	printf("Unesite trazeno/zeljeno prezime");
	scanf("%s", prezime);

	while (p != NULL && _strcmpi(p->prezime, prezime) != 0) {
		p = p->next;
	}
	if (p == NULL) {
		printf("Nije pronadeno\n");
	}
	else {
		printf("Pronadeno");
	}
	return p;
}

// cetvrta fja
void printList(position p)
{
	while (p != NULL)
	{
		printf("%s %s %d", p->ime, p->prezime, &p->godina);
		p = p->next;
	}
}

// peta fja
void deleteElement(position p) {
	position temp;
	char prez[20];

	printf("Unesite prezime od osobe koju zelite izbrisati:\n");
	scanf(" %s", prez);

	while (p->next != NULL && _strcmpi(p->next->prezime, prez) != 0)
	{
		p = p->next;
	}
	temp = p->next;
	if (temp != NULL)
	{
		p->next = temp->next;
		printf("\nIz liste se brise : %s %s %d", temp->ime, temp->prezime, temp->godina);
		free(temp);
	}
}


// sesta fja
void InsertPrev(position P)
{
	position temp;

	temp = FindPrez(P);
	if (temp == NULL)
		printf("\r\nStudent nije pronaden!");
	else
		Insert(temp);
}

position FindPrez(position P)       //za fju insert prev
{
	char prez[20];

	printf("Unesite prezime od osobe koju trazite:\n");
	scanf_s(" %s", prez, 20);
	while (P != NULL & _strcmpi(P->prezime, prez) != 0)
		P = P->next;

	return P;
}

void Insert(position P)    //za fju insert prev, mogli smo koristiti i vec napravljenu fju insertfront
{
	position q;

	q = (position)malloc(sizeof(struct _osoba));
	if (q == NULL)
		printf("error, alokacija memorije nije uspjela\n");
	else
	{
		printf("Unesite ime, prezime i godinu rodenja osobe\n");
		scanf_s(" %s %s %d", q->ime, 20, q->prezime, 20, &q->godina);

		q->next = P->next;
		P->next = q;
	}
}

//sedma fja
void InsertBefore(position P)
{
	position prev;

	prev = FindPrevPrez(P);
	if (prev == NULL)
		printf("Student nije pronaden\n");
	else
		Insert(prev);
}

position FindPrevPrez(position P)       //za fju insertbefore
{
	char prez[20];

	printf("Unesite prezime od osobe koju trazite\n");
	scanf_s(" %s", prez, 20);
	while (P->next != NULL & _strcmpi(P->next->prezime, prez) != 0)
		P = P->next;

	if (P->next == NULL)
		P = NULL;
	return P;
}


//osma fja
void SortList(position P)
{
	position end = NULL, i, j, prev_j;

	while (P->next != end)
	{
		i = P;
		prev_j = i->next;
		j = prev_j->next;

		while (j != end)
		{
			if (_strcmpi(prev_j->prezime, j->prezime) < 0)
			{
				prev_j->next = j->next;
				i->next = j;
				j->next = prev_j;
			}
			else
				i = prev_j;
			prev_j = j;
			j = j->next;
		}
		end = prev_j;
	}
}

// deveta fja
void PrintListToFile(position P)
{
	FILE* fp;
	char imedatot[20];

	printf("Unesite ime vase datoteke:\n");
	scanf_s(" %s", imedatot, 20);

	fp = fopen(imedatot, "w");
	if (fp == NULL)
		printf("Datoteka %s nije uspjesno otvorena \n", imedatot);
	else
	{
		while (P != NULL)
		{
			fprintf(fp, "%s %s %d\r\n", P->ime, P->prezime, P->godina);
			P = P->next;
		}
		fclose(fp);
	}
}

// deseta fja
void ReadListFromFile(position P)
{
	FILE* fp;
	char imedatot[20];
	position q;

	printf("Unesite ime datoteke: \n");
	scanf_s(" %s", imedatot, 20);

	fp = fopen(imedatot, "r");
	if (fp == NULL)
		printf("Datoteka %s nije uspjesno otvorena", imedatot);
	else
	{
		while (!feof(fp))
		{
			q = (position)malloc(sizeof(struct _osoba));
			if (q == NULL)
				printf("error, memorija se nije uspješno alocirala\n");
			else
			{
				fscanf_s(fp, " %s %s %d", q->ime, 20, q->prezime, 20, &q->godina);

				q->next = P->next;
				P->next = q;
			}
		}
		fclose(fp);
	}
}