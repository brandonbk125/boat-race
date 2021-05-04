//
// Created by brb19 on 03/12/2019.
//

#ifndef UNTITLED_FUNCTIONS_H
#define UNTITLED_FUNCTIONS_H

#endif //UNTITLED_FUNCTIONS_H
typedef struct member {
    char familyName[20];
    char firstName[80];
    int membershipID;
    char email[50];
    char boatClass[30];
    char boatName[30];

    struct member *left;
    struct member *right;
} memberNode;

typedef memberNode *memberNodePtr;


memberNodePtr readMember(FILE *memberFile);

void addMember(memberNodePtr current, memberNodePtr new);

memberNodePtr getMembers(char *memberFilename);

void printMembers(memberNodePtr memberPtr);

void lookupMember(int ID, memberNodePtr memberPtr);

void printNode(memberNodePtr memberPtr);

void groupBoatClass(memberNodePtr memberPtr, char boatClass[30]);

memberNodePtr getMemberInfoFromUser();

void preOrder(memberNodePtr memberPtr, FILE *fp);

void saveMembers(char *memberFilename, memberNodePtr memberPtr);

void saveNode(memberNodePtr memberPtr, FILE *fp);



