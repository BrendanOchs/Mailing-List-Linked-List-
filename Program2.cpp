//********************************************************************************
//*                                                                              *
//* PROGRAM FILE NAME: Program2.cpp  ASSIGNMENT#: 2         GRADE: _________     *
//*                                                                              *
//* PROGRAM AUTHOR:________________________________________________              *
//*                                 Brendan Ochs                                 *
//*                                                                              *
//* COURSE#: CSC 36000 SEC 11           DUE DATE: February 8th, 2017             *
//*                                                                              *
//********************************************************************************

//*****************************PROGRAM DESCRIPTION********************************
//*                                                                              *
//*  Purpose:    The purpose of this program is to use a linked List to maintain *
//*              a mailing list. The program will take in any number of entries  *
//*              and only allocate the specific amount of memory per entry.      *
//*              This program will add, delete, change, and print records as     *
//*              specified.                                                      *
//*                                                                              *
//*  USER DEFINED                                                                *
//*  MODULES     :                                                               *
//*               Header- Print output preamble.                                 *
//*               read  - Read in One input from input file.                     *
//*               addNode- Add an entry to the list.                             *
//*               print  - Print out all entries in list.                        *
//*               search - search for duplicate entries.                         *
//*               changeInfo- get info to be changed.                            *
//*               deleteNode- delete an entry from the list.                     *
//*               Footer    - Print output salutaion.                            *
//*               ListClass - Initializes the class private variable pointer.    *
//*                                                                              *
//********************************************************************************


#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <string>

using namespace std;

//****************************************Structure*******************************************
struct NodeType
{
    char firstName[13];
    char lastName[13];
    char address[21];
    char city[13];
    char state[3];
    int zip=0;
    int field=0;
    //**********Pointer********
    NodeType *next;
};
//************************************End of Structure****************************************
//**************************************Class*************************************************
class ListClass
{
    public:
        ListClass();
        void read(ifstream &, NodeType &, char);
        void addNode(ofstream &, NodeType);
        void print(ofstream &);
        int search(ifstream &,ofstream &, NodeType ,char);
        void changeInfo(ifstream &, NodeType &);
        void deleteNode(NodeType);
    
    
    private:
        NodeType *start;
};
//**************************************End Class*********************************************
//************************************Prototypes**********************************************

void Header(ofstream &);
void Footer(ofstream &);


//***********************************End Prototypes*******************************************


int main()
{
        // Create an input stream for input file
    ifstream input("data2.txt",ios::in);
        // Create an output stream for output file
    ofstream output("MailingList.txt",ios::out);
        // Create a temp node
    NodeType mail;
        // Create a ListClass Object
    ListClass list;
        // Create a character to hold the incoming operation
    char opCode;
        // Create a boolean to cancel or continue the program
    bool go=true;
        // Print out out preamble
    Header(output);
    
    while(go)
    {
        input >> opCode;
        if(opCode=='A')
        {
            list.read(input, mail, opCode);
            int found=list.search(input,output,mail,opCode);
            if (found==0)
            {
                list.addNode(output, mail);
            }
        }
        else if(opCode=='D')
        {
            list.read(input, mail, opCode);
            int found=list.search(input,output, mail, opCode);
            if (found==1)
            {
                list.deleteNode(mail);
            }
            else
            {
                output << "Record of " << mail.firstName << " " << mail.lastName
                << " not found."
                << " Attempt to delete record failed." << endl;
            }
        }
        else if (opCode=='C')
        {
            list.read(input, mail, opCode);
            list.changeInfo(input, mail);
            int found=list.search(input,output, mail, opCode);
            if(found==0)
            {
                output << "Record of " << mail.firstName << " " << mail.lastName
                << " not found."
                << " Attempt to change record failed." << endl;
            }
        }
        else if (opCode=='P')
        {
            list.print(output);
        }
        else if (opCode=='Q')
        {
            go=false;
        }
        
        
    }

    Footer(output);
    
    return 0;
}


//*************************************Functions*********************************************
ListClass::ListClass()
{
        //Receives-----------------------------------
        //Task    - Initialize private class variable
        //Returns -----------------------------------
    start=NULL;
}

//*******************************************************************************************
void ListClass::read(ifstream & input, NodeType & mail, char transaction)
{
    // Receives- input file, CustomerType temp
    // Task    - read in one input from input file
    // Returns - input file, CustomerType temp
    
    
    if (transaction=='A')
    {
        input >> ws;
        input.getline(mail.firstName,13);
        input >> ws;
        input.getline(mail.lastName,13);
        input >> ws;
        input.getline(mail.address,21);
        input >> ws;
        input.getline(mail.city,13);
        input >> ws;
        input.getline(mail.state,3);
        input >> ws;
        input >> mail.zip;
    }
    else if (transaction=='D')
    {
        input >> ws;
        input.getline(mail.firstName,13);
        input >> ws;
        input.getline(mail.lastName,13);
    }
    else if (transaction=='C')
    {
        input >> ws;
        input.getline(mail.firstName,13);
        input >> ws;
        input.getline(mail.lastName,13);
    }
}


//*******************************************************************************************


void ListClass::addNode(ofstream & output, NodeType mail)
{
    
        //Receives- mail, start pointer
        //Task    - add a node
        //Returns - output, start
    NodeType *newPtr, *PreviousPtr, *CurrentPtr;
    newPtr= new (NodeType);
    
    if (newPtr==NULL)
        output << "Error, no memory available" << endl;
    else
    {
        strcpy(newPtr->firstName,mail.firstName);
        strcpy(newPtr->lastName,mail.lastName);
        strcpy(newPtr->address,mail.address);
        strcpy(newPtr->city,mail.city);
        strcpy(newPtr->state,mail.state);
        newPtr->zip=mail.zip;
        newPtr->next=mail.next;
        PreviousPtr=NULL;
        CurrentPtr=start;
            while((CurrentPtr!=NULL)&&(strcmp(newPtr->lastName,CurrentPtr->lastName)>0))
            {
                
                PreviousPtr=CurrentPtr;
                CurrentPtr=CurrentPtr->next;
            }
            if(PreviousPtr==NULL)
            {
                newPtr->next=start;
                start=newPtr;
            }
            else
            {
                PreviousPtr->next=newPtr;
                newPtr->next= CurrentPtr;
            }
    }
    
    
}

//***************************************************************************************************

void ListClass::deleteNode(NodeType mail)
{
        //Receives- Mail
        //Task    - delete a specified entry
        //Returns ---------------------------
    NodeType *TempPtr, *PreviousPtr, *CurrentPtr;
    if (strcmp(mail.firstName,start->firstName)==0)
    {
        TempPtr=start;
        start=start->next;
        delete(TempPtr);
    }
    else
    {
        PreviousPtr=start;
        CurrentPtr=start->next;
        while((CurrentPtr!=NULL) && (strcmp(CurrentPtr->firstName,mail.firstName)!=0))
        {
            PreviousPtr=CurrentPtr;
            CurrentPtr=CurrentPtr->next;
        }
        if(CurrentPtr!=NULL)
        {
            TempPtr=CurrentPtr;
            PreviousPtr->next=CurrentPtr->next;
            delete (TempPtr);
        }
    }
    
}






//****************************************************************************************************



int ListClass::search(ifstream & input, ofstream & output, NodeType mail, char opCode)
{
        //Receives- mail, opCode
        //Task    - search for duplicate entry or non existent entry swap if 'C'
        //Returns - 1(found) or 0(not found)
    NodeType *CurrentPtr;
    CurrentPtr= start;
    if(opCode=='A')
    {
        while(CurrentPtr!=NULL)
        {
            if((strcmp(CurrentPtr->lastName,mail.lastName)==0) && (strcmp(CurrentPtr->firstName,mail.firstName)==0))
            {
                output << mail.firstName << "     " << mail.lastName
                << " is already in the list."
                << " Attempt to add duplicate record failed." << endl;
                return 1; //if found
            }
            CurrentPtr=CurrentPtr->next;
        }
    }
    else if (opCode=='D')
    {
        while(CurrentPtr!=NULL)
        {
            if((strcmp(CurrentPtr->lastName,mail.lastName)==0) && (strcmp(CurrentPtr->firstName,mail.firstName)==0))
            {
                return 1; //if found
            }
            CurrentPtr=CurrentPtr->next;
        }
    }
    else if (opCode=='C')
    {
        while(CurrentPtr!=NULL)
        {
            if((strcmp(CurrentPtr->lastName,mail.lastName)==0) && (strcmp(CurrentPtr->firstName,mail.firstName)==0))
            {
                switch(mail.field)
                {
                    case 1: input >> ws; input.getline(mail.firstName,13);
                            strcpy(CurrentPtr->firstName, mail.firstName); return 1;
                    case 2: input >> ws; input.getline(mail.lastName,13);
                            strcpy(CurrentPtr->lastName,mail.lastName); return 1;
                    case 3: input >> ws; input.getline(mail.address,21);
                            strcpy(CurrentPtr->address,mail.address); return 1;
                    case 4: input >> ws; input.getline(mail.city,13);
                            strcpy(CurrentPtr->city,mail.city); return 1;
                    case 5: input >> ws; input.getline(mail.state,3);
                            strcpy(CurrentPtr->state,mail.state); return 1;
                    case 6: input >> mail.zip;
                            CurrentPtr->zip=mail.zip; return 1;
                }
            }
            CurrentPtr=CurrentPtr->next;
        }
    }
    return 0; //if entry not found
}


//**************************************************************************************************










void ListClass::print(ofstream & output)
{
        //Receives- output
        //Task    - prints everyone in the list
        //Returns - output
    NodeType *CurrentPtr;
    CurrentPtr= start;
     if(CurrentPtr==NULL)
     {
         output << "List is Empty" << endl;
     }
    if(CurrentPtr!=NULL)
    {
        output << setw(50) << "MAILING LIST" << endl;
        output << "Last Name" << setw(15) << "First Name" << setw(15) << "Address"
               << setw(17) << "City" << setw(15) << "State" << setw(15)
               << "Zip Code" << endl;
        output << "==============================================================="
               << "===========================" << endl;
        while(CurrentPtr!=NULL)
        {
            output << CurrentPtr->lastName << setw(15)<< CurrentPtr->firstName
            << setw(21) << CurrentPtr->address << setw(15)<< CurrentPtr->city
            << setw(7) << CurrentPtr->state
            << "          " << CurrentPtr->zip << endl;
            CurrentPtr=CurrentPtr->next;
        }
        output << endl << endl;
    }
}




//******************************************************************************************



void ListClass::changeInfo(ifstream & input, NodeType & mail)
{
        //Receives- input file, mail
        //Task    - get field number
        //Returns - input file, mail
    input >> mail.field;
    
}




//********************************** HEADER & FOOTER ****************************************
//*******************************************************************************************

void Header( ofstream &outFile)
{
    // Receives- output file
    // Task    - prints the output preamble
    // Returns - nothing
    outFile << setw(30) << "Brendan Ochs";
    outFile << setw(17) << "CSC 36000";
    outFile << setw(15) << "Section 11" << endl;
    outFile << setw(30) << "Spring 2017";
    outFile << setw(20) << "Assignment #2" << endl;
    outFile << setw(35) << "-----------------------------------";
    outFile << setw(35) << "-----------------------------------" << endl << endl;
    return;
}

//***************************************FOOTER*******************************************
//****************************************************************************************

void Footer(ofstream &outFile)
{
    // Receives- the output file
    // Task    - prints the output salutation
    // Returns - nothing
    outFile << endl;
    outFile << setw(35) << "---------------------------------" << endl;
    outFile << setw(35) << "|------END OF PROGRAM OUTPUT-------|" << endl;
    outFile << setw(35) << "---------------------------------" << endl;
    
    return;
}


















