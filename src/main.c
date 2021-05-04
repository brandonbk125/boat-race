#include <stdio.h>
#include "functions.h"

int main() {
    char pathname[100];
    printf("Enter path of file to open: ");
    scanf(" %[^\n]", pathname);

    memberNodePtr rootNode;
    rootNode = getMembers(pathname);


    int answer;

    do {
        printf("\tMenu: \n 1: List members \n"
               " 2: Search memberID \n "
               "3: Boat class list \n "
               "4: Add new member \n "
               "-1: Save and exit\n");
        printf("Enter choice: ");
        scanf(" %d", &answer);
        switch (answer) {

            case 1:
                printMembers(rootNode);
                break;
            case 2:;
                int ID;
                printf("Enter member ID to lookup: ");
                scanf(" %d", &ID);
                lookupMember(ID, rootNode);
                break;
            case 3:;
                char uBoatClass[30];
                printf("Enter boat class to look up: ");
                scanf(" %s", uBoatClass);
                groupBoatClass(rootNode, uBoatClass);
                break;
            case 4:
                addMember(rootNode, getMemberInfoFromUser());
                break;
            case -1:
                saveMembers(pathname, rootNode);
                break;
            default:
                break;
        }
    } while (answer != -1);


    return 0;
}