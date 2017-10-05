#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//Jason Wang
typedef struct address { //defining each node and what is in it
	char firstname[256];
	char lastname[256];
	char startadd[256];
	char endadd[256];
	char phone[256];
	struct address* next;
} Node;

Node *head = NULL;

char* getCity(char* endadd) { //getting the City from the input line
	char* city = (char*)malloc(sizeof(char*));
	for(int i = 0; i < strlen(endadd) - 1; i++) {
		if (endadd[i] >= 'A' && endadd[i] <= 'Z') {
			if (endadd[i+1] >= 'A' && endadd[i+1] <= 'Z') {
				strncpy(city, endadd, i-1);
			}
		}
	}
	return city;
	free(city);
}
char* getState(char* endadd) { //Getting the state from the input line
	char* state = (char*)malloc(sizeof(char*));
	for(int i = 0; i < strlen(endadd) - 1; i++) {
		if (endadd[i] >= 'A' && endadd[i] <= 'Z') {
			if (endadd[i+1] >= 'A' && endadd[i+1] <= 'Z') {
				strncpy(state, endadd, i+2);
			}
		}
	}
	return state;
	free(state);
}

void add(char first[], char last[], char start[], char end[], char ph[]) {
	struct address *newAdd;
	newAdd = (struct address*)malloc(sizeof(struct address));
	strcpy(newAdd->firstname, first);
	strcpy(newAdd->lastname, last);
	strcpy(newAdd->startadd, start);
	strcpy(newAdd->endadd, end);
	strcpy(newAdd->phone, ph);
	newAdd->next = NULL;
	if(head == NULL) { //If there is nothing in the head just put that node as the head
		head = newAdd;
	}
	else {
		Node *curr = head;
		char* headCity = getCity(head->endadd);
		char* newCity = getCity(newAdd->endadd);
		char* newState = getState(newAdd->endadd);
		if (strcmp(headCity, newCity) > 0) { //If it is before the first node in the list make it the head of the linked list
			newAdd->next = head;
			head = newAdd;
		}
		else if (strcmp(headCity, newCity) < 0) {
			while (curr->next != NULL) {
				char* currCity = getCity(curr->endadd);
				char* nextCity = getCity(curr->next->endadd);
				if (strcmp(nextCity, newCity) < 0) { //If it is still after current->next move through the list
					curr = curr->next;
				}
				else if (strcmp(nextCity, newCity) > 0){ //If it is after current but before current->next put the node in between them
					newAdd->next = curr->next;
					curr->next = newAdd;
					curr = newAdd;
					break;
				}
				else { //Do the same thing as above but for state then lastname then firstname
					char* currState = getState(curr->endadd);
					char* nextState = getState(curr->next->endadd);
					if (strcmp(nextState, newState) < 0) {
						curr = curr->next;
					}
					else if (strcmp(nextState, newState) > 0){
						newAdd->next = curr->next;
						curr->next = newAdd;
						curr = newAdd;
						break;
					}
					else {
						if (strcmp(curr->next->lastname,newAdd->lastname) < 0) {
							curr = curr->next;
						}
						else if (strcmp(curr->next->lastname, newAdd->lastname) > 0) {
							newAdd->next = curr->next;
							curr->next = newAdd;
							curr = newAdd;
							break;
						}
						else {
							if (strcmp(curr->next->firstname, newAdd->firstname) < 0) {
								curr = curr->next;
							}
							else if (strcmp(curr->next->firstname, newAdd->firstname) >= 0) {
								newAdd->next = curr->next;
								curr->next = newAdd;
								curr = newAdd;
								break;
							}
						}
					}
				}
			}
		}
		else { //Do the following as above but for states
		//This only applies if the new Node has the same city as the first node in the linked list
			char* headState = getState(head->endadd);
			char* newState = getState(newAdd->endadd);
			if (strcmp(headState, newState) > 0) {
				newAdd->next = head;
				head = newAdd;
			}
			else if (strcmp(headState, newState) < 0) {
				while (curr->next != NULL) {
					char* currCity = getCity(curr->endadd);
					char* nextCity = getCity(curr->next->endadd);
					if (strcmp(nextCity, newCity) < 0) {
						curr = curr->next;
					}
					else if (strcmp(nextCity, newCity) > 0){
						newAdd->next = curr->next;
						curr->next = newAdd;
						curr = newAdd;
						break;
					}
					else {
						char* currState = getState(curr->endadd);
						char* nextState = getState(curr->next->endadd);
						if (strcmp(nextState, newState) < 0) {
							curr = curr->next;
						}
						else if (strcmp(nextState, newState) > 0){
							newAdd->next = curr->next;
							curr->next = newAdd;
							curr = newAdd;
							break;
						}
						else {
							if (strcmp(curr->next->lastname,newAdd->lastname) < 0) {
								curr = curr->next;
							}
							else if (strcmp(curr->next->lastname, newAdd->lastname) > 0) {
								newAdd->next = curr->next;
								curr->next = newAdd;
								curr = newAdd;
								break;
							}
							else {
								if (strcmp(curr->next->firstname, newAdd->firstname) < 0) {
									curr = curr->next;
								}
								else if (strcmp(curr->next->firstname, newAdd->firstname) >= 0) {
									newAdd->next = curr->next;
									curr->next = newAdd;
									curr = newAdd;
									break;
								}
							}
						}
					}
				}
			}
			else { //Do the following but for lastname
			//This only applies if the new Node has the same city and same state as the first node in the linked list
				if (strcmp(head->lastname, newAdd->lastname) > 0) {
					newAdd->next = head;
					head = newAdd;
				}
				else if (strcmp(head->lastname, newAdd->lastname) < 0) {
					while (curr->next != NULL) {
						char* currCity = getCity(curr->endadd);
						char* nextCity = getCity(curr->next->endadd);
						if (strcmp(nextCity, newCity) < 0) {
							curr = curr->next;
						}
						else if (strcmp(nextCity, newCity) > 0){
							newAdd->next = curr->next;
							curr->next = newAdd;
							curr = newAdd;
							break;
						}
						else {
							char* currState = getState(curr->endadd);
							char* nextState = getState(curr->next->endadd);
							if (strcmp(nextState, newState) < 0) {
								curr = curr->next;
							}
							else if (strcmp(nextState, newState) > 0){
								newAdd->next = curr->next;
								curr->next = newAdd;
								curr = newAdd;
								break;
							}
							else {
								if (strcmp(curr->next->lastname,newAdd->lastname) < 0) {
									curr = curr->next;
								}
								else if (strcmp(curr->next->lastname, newAdd->lastname) > 0) {
									newAdd->next = curr->next;
									curr->next = newAdd;
									curr = newAdd;
									break;
								}
								else {
									if (strcmp(curr->next->firstname, newAdd->firstname) < 0) {
										curr = curr->next;
									}
									else if (strcmp(curr->next->firstname, newAdd->firstname) >= 0) {
										newAdd->next = curr->next;
										curr->next = newAdd;
										curr = newAdd;
										break;
									}
								}
							}
						}
					}
				}
				else { //Do the following for firstname
				//This only applies if the new Node has the same city, state, and firstname as the first node in the linked list
					if (strcmp(head->firstname, newAdd->firstname) > 0) {
						newAdd->next = head;
						head = newAdd;
					}
					else if (strcmp(head->firstname, newAdd->firstname) <= 0) {
						while (curr->next != NULL) {
							char* currCity = getCity(curr->endadd);
							char* nextCity = getCity(curr->next->endadd);
							if (strcmp(nextCity, newCity) < 0) {
								curr = curr->next;
							}
							else if (strcmp(nextCity, newCity) > 0){
								newAdd->next = curr->next;
								curr->next = newAdd;
								curr = newAdd;
								break;
							}
							else {
								char* currState = getState(curr->endadd);
								char* nextState = getState(curr->next->endadd);
								if (strcmp(nextState, newState) < 0) {
									curr = curr->next;
								}
								else if (strcmp(nextState, newState) > 0){
									newAdd->next = curr->next;
									curr->next = newAdd;
									curr = newAdd;
									break;
								}
								else {
									if (strcmp(curr->next->lastname,newAdd->lastname) < 0) {
										curr = curr->next;
									}
									else if (strcmp(curr->next->lastname, newAdd->lastname) > 0) {
										newAdd->next = curr->next;
										curr->next = newAdd;
										curr = newAdd;
										break;
									}
									else {
										if (strcmp(curr->next->firstname, newAdd->firstname) < 0) {
											curr = curr->next;
										}
										else if (strcmp(curr->next->firstname, newAdd->firstname) >= 0) {
											newAdd->next = curr->next;
											curr->next = newAdd;
											curr = newAdd;
											break;
										}
									}
								}
							}
						}
					}	
				}
			}
		}
		if (newAdd->next == NULL) {
			curr->next = newAdd;
		}
	}
}

void removed(char first[], char last[]) {
	Node *curr = head;
	while (curr->next != NULL) {
		if (curr->next->next != NULL) {
			if ((strcmp(curr->next->firstname,first) == 0) && (strcmp(curr->next->lastname, last) == 0)) {
				curr->next = curr->next->next;
				break;	
			}
			else {
				curr = curr->next;
			}
		}
		else {
			if ((strcmp(curr->next->firstname,first)) == 0 && (strcmp(curr->next->lastname, last) == 0)) {
				Node *temp = curr->next;
				curr->next = NULL;
			}
		} 
	}		
} 

int main() {
	char line[256];
	int count = 0;
	while(fgets(line, sizeof(line), stdin)) { //Get each of the lines in the input file
		char first[sizeof(line)];
		char last[sizeof(line)];
		char start[sizeof(line)];
		char end[sizeof(line)];
		char ph[sizeof(line)];
		if(count == 0) {
			strcpy(first,line);
			count++;
		}
		else if(count == 1) {
			strcpy(last,line);
			count++;
		}
		else if(count == 2) {
			strcpy(start,line);
			count++;
		}
		else if(count == 3) {
			strcpy(end,line);
			count++;
		}
		else if(count == 4) {
			strcpy(ph,line);
			add(first,last,start,end,ph); //Add that person as a node to the linked list
			count++;
		}
		else if(count == 5) {
			count = 0;
		}
	}
	Node *fprinted = head;
        while (fprinted != NULL) {
                char* city = getCity(fprinted->endadd);
                printf("%s %s %s\n",strtok(fprinted->firstname, "\n"), strtok(fprinted->lastname, "\n"), city);
                fprinted = fprinted->next;
        }
	printf("\n");
	char peng[5][256] = {"Pengfei", "Zheng", "123 Maple Drive", "Durham NC 27705", "(919) 660-5555"};
	char alfr[5][256] = {"Alfredo", "Velasco", "456 Walnut Drive", "Durham NC 27708", "(919) 660-5056"};
	char ben[5][256] = {"Ben", "Lee", "789 Chestnut Street", "Durham NC 27708", "(919) 660-5057"};
	add(peng[0],peng[1],peng[2],peng[3],peng[4]); //Add Pengfei
	add(alfr[0],alfr[1],alfr[2],alfr[3],alfr[4]); //Add Alfredo
	add(ben[0],ben[1],ben[2],ben[3],ben[4]); //Add Ben
	removed(peng[0],peng[1]); //Remove Pengfei
        removed(alfr[0],alfr[1]); //Remove Alfredo
	Node *printed = head;
	while (printed != NULL) {
		char* city = getCity(printed->endadd);
		printf("%s %s %s\n",strtok(printed->firstname, "\n"), strtok(printed->lastname, "\n"), city);
		printed = printed->next;
	}
	Node *freed = head;
	Node *temp;
	while (freed != NULL) {
		temp = freed;
		freed = freed->next;
		free(temp);
	}
	//free(head);
	
}
