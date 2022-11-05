#include <iostream>
#include <string>

#include "p3.h"

using namespace std;

Info::Info() {
    this->name = "No Name Set";
    this->value = "No Value Set";
    this->next = nullptr;
}

Info::Info(std::string name, std::string value, Info *next) {
    this->name = name;
    this->value = value;
    this->next = next;
}

Contact::Contact() {
    this->first = "No First Set";
    this->last = "No Last Set";
    this->next = nullptr;
    this->headInfoList = nullptr;
}

Contact::Contact(std::string first, std::string last, Contact *next) {
    this->first = first;
    this->last = last;
    this->next = next;
    this->headInfoList = nullptr;
}

ContactList::ContactList() {
    this->headContactList = nullptr;
    this->count = 0;
}

int ContactList::getCount() {
    return this->count;
}

// print the specified contact and its information
// 1. return false and print nothing if the contact is not in the list
// 2. otherwise return true and print the contact
bool ContactList::printContact(std::ostream &os, std::string first, std::string last) {
    if (checkListFL(first, last) == false) return false;
    Contact* temp = searchContact(first,last);//similar process to print, but only check if next info is empty
    os << "Contact Name: " << temp->first << " " << temp->last << endl;
    if (temp->headInfoList != nullptr){
        Info* tempInfo = temp->headInfoList;
        while (tempInfo != nullptr){
            if (tempInfo->next == nullptr){
                os << "    " << tempInfo->name << " | " << tempInfo->value;
                tempInfo = tempInfo->next;
            }
            else{
                os << "    " << tempInfo->name << " | " << tempInfo->value;
                tempInfo = tempInfo->next;
            }
        }
        return true;
    }
    return true;
}

// print all contacts and their information
// print nothing if the list is empty
void ContactList::print(std::ostream &os) {
    //cout << "In print" << endl;
    Contact* temp = headContactList;//current pointer
    
    //int i = 0;
    while(temp != nullptr){//iterate through fill list
        //os << i << ": ";
        if (temp->headInfoList == nullptr && temp->next == nullptr)//if this contact has no info and next contact is empty, output with no end line
            os << "Contact Name: " << temp->first << " " << temp->last;
        else    os << "Contact Name: " << temp->first << " " << temp->last << endl;//otherwise output contact with end line
        if (temp->headInfoList != nullptr){//if info list is not empty
            Info* tempInfo = temp->headInfoList;//current info pointer
            while(tempInfo != nullptr){//iterate through info
                if((temp->next == nullptr) && (tempInfo->next == nullptr)){//if the next contact and next info is null, output with no endl
                    os << "    " << tempInfo->name << " | " << tempInfo->value;
                    break;
                }
                else{
                    os << "    " << tempInfo->name << " | " << tempInfo->value << endl;
                    
                }
                tempInfo = tempInfo->next;
            }
        }
        temp = temp->next;
        //i++;
    }
}

// add a contact to the back of the list
// 1. return false and do nothing if the contact is already in the list
// 2. otherwise return true and add the contact to the back of the list
// - do not forget to update count
bool ContactList::addContact(std::string first, std::string last) {
    // Contact* newContact = new Contact;//create new contact with first and last set, next and headinfolist null
    // newContact->first = first;
    // newContact->last = last;
    // newContact->next = nullptr;
    // newContact->headInfoList = nullptr;              //this does not allow a destructor if i dont call constructor
    Contact* newContact = new Contact(first,last,nullptr);
    
    if (headContactList == nullptr){//if list is empty add to front and increase count
        headContactList = newContact;
        this->count++;
        return true;
    }
    else{
        if(this->checkList(newContact) == false){//if contact is in the list return false
            if (headContactList-> next != nullptr){
                Contact* temp = headContactList;//current pointer

                while(temp->next != nullptr){//find end of list
                    temp = temp->next;
                }
                temp->next = newContact;//add contact to end
            }
            else{
                headContactList->next = newContact;//otherwise add front
            }
                this->count++;
            
                return true;
        }
        else return false;
    }
}

bool ContactList::checkList(Contact* toCheck){
    //cout << "in checkList" << endl;
    Contact* temp = headContactList;//check list by the contact, return true if found
    //cout << "before while loop" << endl;
    while(temp != nullptr){
        //cout << "in while loop" << endl;
        if (temp->first == toCheck->first && temp->last == toCheck->last){
            return true;
        }
        temp = temp->next;
    }

    return false;
}

bool ContactList::checkListFL(std::string first, std::string last){
    //cout << "in checkList" << endl;
    Contact* temp = headContactList;
    //cout << "before while loop" << endl;
    while(temp != nullptr){//check list by first and last name, return true if found
        //cout << "in while loop" << endl;
        if (temp->first == first && temp->last == last){
            return true;
        }
        temp = temp->next;
    }
    //cout << first<<" not found" << endl;
    return false;
}

// void traverseToFL(Contact* list,std::string first, std::string last)

bool ContactList::checkInfo(std::string infoName, std::string first, std::string last){
    //cout << "in checkInfo" << endl;
    Contact* temp = searchContact(first,last);//current contact
    Info* tempInfo = temp->headInfoList;//current info is head of current contact info list
    while(tempInfo != nullptr){//iterate through  list
        if (tempInfo->name == infoName){
            //cout << "outputting true in CheckInfo " << endl;
            return true;//if found return true
        }
        tempInfo = tempInfo->next;

    }

    //cout << "outputting false in CheckInfo " << endl;
    return false;


}

Contact* ContactList::searchContact(std::string first,std::string last){
    Contact* temp = headContactList;//current pointer
    while(temp->first !=first && temp->last != last){//iterate until contact is found
            temp = temp->next;
            //cout << "in traversal" << endl;
        }
    return temp;//return the current pointer/node
}

// add info to the back of a contact's info list
// 1. return false and do nothing if the contact is not in the list
// 2. if the infoName is already in the info list, update the infoValue and return true
// 3. otherwise add the info to the back of the contact's list and return true
bool ContactList::addInfo(std::string first, std::string last, std::string infoName, std::string infoVal) {
    //cout << "in very beginning addInfo" << endl;
    // Info* toAdd = new Info;//create new info pointer and assign 
    // toAdd->name = infoName;
    // toAdd->value = infoVal;
    // toAdd->next = nullptr;           same issue as addContact
    Info* toAdd = new Info(infoName,infoVal,nullptr);
    //cout << "in addInfo" << endl;
    if (headContactList == nullptr){//if the list is empty return false
            return false;
        }

    if (checkListFL(first,last)==false)return false;//if the contact is not in the list return false
    else{
        Contact* temp = searchContact(first,last);//assign current contact to the correct contact
        if (temp->headInfoList==nullptr){//if the info list is emty, assign head to the new node
            temp->headInfoList=toAdd;
            return true;
        }
        else if(checkInfo(infoName, first,last)== true){//if info exists, 
            Info* tempInfo = temp->headInfoList;//current info pointer is head of current contact
            while (tempInfo->next !=nullptr){//iterate until info is found
                if (tempInfo->name == infoName) break;
                tempInfo = tempInfo->next;

            }
            tempInfo->value = infoVal;//update the value
            //cout << "adding info for (case 2) "<< temp->first << endl;
            return true;
        }
        else{
            Info* tempInfo = temp->headInfoList;//current info pointer is head info list
            while (tempInfo->next !=nullptr){//iterate to end
                tempInfo = tempInfo->next;

            }
            //cout << "adding info for "<< temp->first << endl;
            tempInfo->next = toAdd;//add info to end
            return true;
        }

    }

}

// add a contact to the list in ascending order by last name
//     if last names are equal, then order by first name ascending
// 1. return false and do nothing if the contact is already in the list
// 2. otherwise return true and add the contact to the list
// - do not forget to update count
// - compare strings with the built-in comparison operators: <, >, ==, etc.
// - a compare method/function is recommended


bool compareContact(Contact* toAdd, Contact* compareTo){
    if (compareTo->last > toAdd->last){
        return true;                        //if next contact is greater, return true
    }
    else if (compareTo->last < toAdd->last){
        return false;                       //if next contact is less, return false
    }
    else{
        if (compareTo->first > toAdd->first){       //by first names since last equal
        return true;                        //if next contact is greater, return true
        }
        else if (compareTo->first < toAdd->first){
        return false;                       //if next contact is less, return true
        }

    }
}
bool ContactList::addContactOrdered(std::string first, std::string last) {
    // Contact* newContact = new Contact;//create new contact and assign all values. next and headInfoList are null
    // newContact->first = first;
    // newContact->last = last;
    // newContact->next = nullptr;
    // newContact->headInfoList = nullptr;      same issue
    Contact* newContact = new Contact(first,last,nullptr);

    if (headContactList == nullptr){//if the list currently is null, head is new contact
        headContactList = newContact;
        this->count++;
        return true;
    }
    else if (checkListFL(first,last)==true) return false;//if the contact does not exist in the list return false
    else{
            if (compareContact(newContact,headContactList) == true){//if newContact is less than head add front
                newContact->next = headContactList;
                headContactList = newContact;
                this->count++;
                return true;

            }
            Contact* temp = headContactList->next;//make next and previous pointers
            Contact* previous = headContactList;
            while(temp!=nullptr){//iterate through until the correct insertion spot is found
                if (compareContact(newContact,temp) == true){
                    break;
                }
                previous = previous->next;
                temp = temp->next;
            }
            previous->next = newContact;//add new contact between previous and current
            newContact->next = temp;
            count++;//increase count by one
            return true;
            
        //     while(temp != nullptr){
        //         if (temp->next->last > newContact->last){
        //             newContact->next = temp->next;
        //             temp->next = newContact;
        //             this->count++;
        //             return true;
        //         }
        //         else if((temp->next->last) == (newContact->last)){
        //             if (temp->next->first > newContact->first){
        //                 newContact->next = temp->next;
        //                 temp->next = newContact;                                         //this caused me segFaults, not sure why
        //                 this->count++;                                                   //class example better
        //                 return true;
        //             }
        //         }
        //         else if(temp->next == nullptr){
        //             newContact->next = nullptr;
        //             temp->next = newContact;
        //             this->count++;
        //             return true;
        //         }
        //         temp = temp->next;
        //     }
        // }
        //else return false;

    }
    return true;

}

bool compareInfo(Info* newInfo,Info* temp){//returns true if newInfo is less than temp, false otherwise
    if (newInfo->name < temp->name){
        return true;
    }
    else{
        return false;
    }

}

// add info to a contact's info list in ascending order by infoName
// 1. return false and do nothing if the contact is not in the list
// 2. if the infoName is already in the info list, update the infoValue and return true
// 3. otherwise add the info to the contact's list and return true
bool ContactList::addInfoOrdered(std::string first, std::string last, std::string infoName, std::string infoVal) {
    // Info* newInfo = new Info;//create a new Info pointer for the new info and assign name,value, and next to null
    // newInfo->name=infoName;
    // newInfo->value=infoVal;
    // newInfo->next=nullptr;           same issue
    Info* newInfo = new Info(infoName,infoVal,nullptr);
    
    if (headContactList == nullptr){//if contact list is empty return false
        return false;
    }
    
    //cout << "created temp contact" << endl;
    if(checkListFL(first,last) == false)return false;//if  the contact is not in contact list return false
    //cout << "past first if" << endl;
    Contact* tempContact = searchContact(first,last);//go to correct contact
    if (tempContact->headInfoList==nullptr){//if info list is empty, head is the new node
        tempContact->headInfoList=newInfo;
        return true;
    }
    else if(checkInfo(infoName, first,last)== true){//if the infoname already exists
            //cout << "past if statement" <<endl;
            Info* tempInfo = tempContact->headInfoList;//current pointer
            //cout << "made tempInfo" << endl;
            while (tempInfo !=nullptr){//iterate through info list until infoName is founf
                if (tempInfo->name == infoName) break;
                tempInfo = tempInfo->next;

            }
            tempInfo->value = infoVal;//update the value
            //cout << "adding info for (case 2) "<< temp->first << endl;
            return true;
            //cout << "past first in if else if else if..." << endl;
        }
    
    else if (compareInfo(newInfo,tempContact->headInfoList)==true){//if the new info is less than the head, insert at front
        newInfo->next=tempContact->headInfoList;
        tempContact->headInfoList=newInfo;
        return true;
    }
    else{//otherwise
        Info* previous = tempContact->headInfoList;//previous pointer is head of info list
        Info* tempInfo = tempContact->headInfoList->next;//current is next
        while (tempInfo != nullptr){//iterate through info
            if(compareInfo(newInfo,tempInfo)==true){//if new info is less than the current node stop iterating
                break;
            }
            previous = previous->next;
            tempInfo = tempInfo->next;
        }
        previous->next=newInfo;//add info between previous and current
        newInfo->next=tempInfo;
        return true;
    }

}

// remove the contact and its info from the list
// 1. return false and do nothing if the contact is not in the list
// 2. otherwise return true and remove the contact and its info
// - do not forget to update count
bool ContactList::removeContact(std::string first, std::string last) {
    if (checkListFL(first,last)==false) return false;//is contact in the list
    else if (headContactList->first == first && headContactList->last == last){//if the contact to delete is the head
        Contact* toDelete = headContactList;//mark the node for deletion
        //Contact* newHead = headContactList->next;
        headContactList = headContactList->next;//make the head the next node
        delete toDelete;//delete toe head node from memory
        count--;//decrease count
        return true;
    }
    else {//otherwise:contact to remove is at middle or end
        Contact* tempContact = headContactList->next;//current pointer
        Contact* previous = headContactList;//previous pointer is head
            while(tempContact!=nullptr){//iterate through list
                if (tempContact->first == first&& tempContact->last == last){//if found break
                    break;
                }
                previous = previous->next;//move to next
                tempContact = tempContact->next;
            }
        previous->next = tempContact->next;//previous node points to the next node of current
        delete tempContact;//delete current from memory
        count--;//decrease count by one
        return true;
    }
}


// remove the info from a contact's info list
// 1. return false and do nothing if the contact is not in the list
// 2. return false and do nothing if the info is not in the contact's info list
// 3. otherwise return true and remove the info from the contact's list
bool ContactList::removeInfo(std::string first, std::string last, std::string infoName) {
    if (checkListFL(first,last)==false)return false;//check if the name is in the list
    if (checkInfo(infoName,first,last) == false)return false;//check if the list has info
    Contact* tempContact = searchContact(first,last);//find the contact to remove info from
    if (tempContact->headInfoList->name==infoName){//if info to remove is first in info list
        Info* toDelete = tempContact->headInfoList;//the node to delete is the head
        tempContact->headInfoList = tempContact->headInfoList->next;//make the head head->next
        delete toDelete;//delete old head
        return true;
    }
    else{
        Info* previous = tempContact->headInfoList;//previous pointer is head on the info list
        Info* tempInfo = tempContact->headInfoList->next;//current pointer is next
        while (tempInfo != nullptr){//iteratje through info list
            if(tempInfo->name == infoName){//if the current pointer matches stop iterating
                break;
            }
            previous = previous->next;//move to next
            tempInfo = tempInfo->next;
        }
        previous->next = tempInfo->next;//previous next points to current next
        delete tempInfo;//delete current node from memory
        return true;

    }
}

void ContactList::clear(){
    while(headContactList!=nullptr){//iterate through head until list is empty
        while (headContactList->headInfoList!=nullptr){//iterate through info of current contact until empty
            removeInfo(headContactList->first,headContactList->last,headContactList->headInfoList->name);//remove info
        }
        removeContact(headContactList->first,headContactList->last);//remove current contact
    }
    count = 0;//list is empty, count is zero
}

// destroy the list by removing all contacts and their infos
ContactList::~ContactList() {
    clear();
}

void ContactList::deepCopy(const ContactList &src){//need to deep copy for assignment, so making a method
    Contact* temp = src.headContactList;//make the temporary(current) pointer the source of copy
    while(headContactList!=nullptr){//iterate through source
        addContact(temp->first,temp->last);//add each contact from src to new list
        Info* tempInfo = temp->headInfoList;//the current info pointer is set to the head of the current contact's headInfoList
        while(tempInfo!= nullptr){//iterate
            addInfo(temp->first,temp->last,tempInfo->name,tempInfo->value);//add all info to current contact
        }
        count = src.count;//copy count over
    }
}

// deep copy the source list
// - do not forget to update count
ContactList::ContactList(const ContactList &src) {                  //deep copy makes a new contactList with same attributes as old contactList
    headContactList = nullptr;//make headContactList empty
    deepCopy(src);//deepcopy src to headContactList
}

// remove all contacts and their info then deep copy the source list
// - do not forget to update count
const ContactList &ContactList::operator=(const ContactList &src) {
    if (this != &src) {//first check to see if src and comparison are equal
        clear();//if not clear headContactList and copy src to it
        deepCopy(src);
    }
    return *this;
}
