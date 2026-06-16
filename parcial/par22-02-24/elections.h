#ifndef ELECTIONS_H
#define ELECTIONS_H

typedef struct {
	int number;
	int party;
	int electoralSection;
	int district;
} tVote;

typedef struct {
	int party
	char name[101];
} tParty;

typedef struct {
	int districtID;
	char name[101];
	int electoralSectionID;
} tDistrict;

#endif
