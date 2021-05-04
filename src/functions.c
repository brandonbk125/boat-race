//
// Created by brb19 on 03/12/2019.
//
#include "stdio.h"
#include "functions.h"
#include "stdlib.h"
#include "string.h"


memberNodePtr readMember(FILE *memberFile) {
    int scanStatus;
    memberNode *tempMemberNode;
    tempMemberNode = calloc(1, sizeof(memberNode));
    scanStatus = fscanf(memberFile, "%s\n%[^\n]%d\n%s\n%[^\n]\n%[^\n]\n",
                        tempMemberNode->familyName,
                        tempMemberNode->firstName,
                        &tempMemberNode->membershipID,
                        tempMemberNode->email,
                        tempMemberNode->boatClass,
                        tempMemberNode->boatName);

    if (scanStatus == EOF) {
        free(tempMemberNode);
        return NULL;
    } else {
        return tempMemberNode;
    }
}

void addMember(memberNodePtr current, memberNodePtr new) {
    //compares the nodes by their family name to determine where it should go

    if (strcmp(new->familyName, current->familyName) > 0) {
        //if new > current
        if (current->right == NULL) {
            current->right = new;
        } else {
            addMember(current->right, new);
        }
    } else {
        //if new < current
        if (current->left == NULL) {
            current->left = new;
        } else {
            addMember(current->left, new);
        }

    }
}


memberNodePtr getMembers(char *memberFilename) {

    FILE *memberFile;
    memberNodePtr rootNodePtr;
    memberNodePtr tempMemberPtr;
    //open the member file
    memberFile = fopen(memberFilename, "r");

    if (memberFile != NULL) {
        rootNodePtr = readMember(memberFile);
        while ((tempMemberPtr = readMember(memberFile)) != NULL) {
            addMember(rootNodePtr, tempMemberPtr);
        }

    } else {
        return NULL;
    }

    //close the file
    fclose(memberFile);
    return rootNodePtr;
}

void printMembers(memberNodePtr memberPtr) {
    //print all of the members in order
    if (memberPtr != NULL) {
        printMembers(memberPtr->left);
        printNode(memberPtr);
        printMembers(memberPtr->right);
    }
}


void printNode(memberNodePtr memberPtr) {
    printf("%s, %s, %d, %s, %s, %s \n",
           memberPtr->familyName,
           memberPtr->firstName,
           memberPtr->membershipID,
           memberPtr->email,
           memberPtr->boatClass,
           memberPtr->boatName);
}

void lookupMember(int ID, memberNodePtr memberPtr) {
    //searching for a member given their membershipID using recursion
    if (memberPtr == NULL) {
        return;
    }

    if (memberPtr->membershipID == ID) {
        printNode(memberPtr);
    } else {
        lookupMember(ID, memberPtr->left);
        lookupMember(ID, memberPtr->right);
    }
}

void groupBoatClass(memberNodePtr memberPtr, char boatClass[30]) {

    if (memberPtr == NULL) {
        return;
    }

    if (strcmp(memberPtr->boatClass, boatClass) == 0) {
        printf("%s, %s, %d, %s \n",
               memberPtr->familyName,
               memberPtr->firstName,
               memberPtr->membershipID,
               memberPtr->boatName);
    }
    groupBoatClass(memberPtr->left, boatClass);
    groupBoatClass(memberPtr->right, boatClass);

}

memberNodePtr getMemberInfoFromUser() {


    memberNode *tempNode;
    //assign memory for the memberNode
    tempNode = calloc(1, sizeof(memberNode));

    printf("Enter member first name: ");
    scanf(" %[^\n]", tempNode->firstName);
    printf("Enter member family name: ");
    scanf(" %s", tempNode->familyName);
    printf("Enter member ID: ");
    scanf(" %d", &tempNode->membershipID);
    printf("Enter member email address: ");
    scanf(" %s", tempNode->email);
    printf("Enter boat class: ");
    scanf(" %s", tempNode->boatClass);
    printf("Enter boat name: ");
    scanf(" %[^\n]", tempNode->boatName);


    return tempNode;

}

void preOrder(memberNodePtr memberPtr, FILE *fp) {

    if (memberPtr != NULL) {

        printNode(memberPtr);
        saveNode(memberPtr, fp);
        preOrder(memberPtr->left, fp);
        preOrder(memberPtr->right, fp);

    }

}

void saveNode(memberNodePtr memberPtr, FILE *fp) {
    //write the data to the file
    fprintf(fp, "%s\n", memberPtr->familyName);
    fprintf(fp, "%s\n", memberPtr->firstName);
    fprintf(fp, "%d\n", memberPtr->membershipID);
    fprintf(fp, "%s\n", memberPtr->email);
    fprintf(fp, "%s\n", memberPtr->boatClass);
    fprintf(fp, "%s\n", memberPtr->boatName);
}

void saveMembers(char *memberFilename, memberNodePtr memberPtr) {

    FILE *memberFile;
    //open the file in write mode
    memberFile = fopen(memberFilename, "w");
    preOrder(memberPtr, memberFile);


    fclose(memberFile);
}