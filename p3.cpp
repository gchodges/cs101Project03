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
    Contact* temp = searchContact(first,last);
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
    Contact* temp = headContactList;
    
    //int i = 0;
    while(temp != nullptr){
        //os << i << ": ";
        if (temp->headInfoList == nullptr && temp->next == nullptr)
            os << "Contact Name: " << temp->first << " " << temp->last;
        else    os << "Contact Name: " << temp->first << " " << temp->last << endl;
        if (temp->headInfoList != nullptr){
            Info* tempInfo = temp->headInfoList;
            while(tempInfo != nullptr){
                if((temp->next == nullptr) && (tempInfo->next == nullptr)){
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
    Contact* newContact = new Contact;
    newContact->first = first;
    newContact->last = last;
    newContact->next = nullptr;
    newContact->headInfoList = nullptr;
    
    if (headContactList == nullptr){
        headContactList = newContact;
        this->count++;
        return true;
    }
    else{
        if(this->checkList(newContact) == false){
            if (headContactList-> next != nullptr){
                Contact* temp = headContactList;

                while(temp->next != nullptr){
                    temp = temp->next;
                }
                temp->next = newContact;
            }
            else{
                headContactList->next = newContact;
            }
                this->count++;
            
                return true;
        }
        else return false;
    }
}

bool ContactList::checkList(Contact* toCheck){
    //cout << "in checkList" << endl;
    Contact* temp = headContactList;
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
    while(temp != nullptr){
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
    Contact* temp = searchContact(first,last);
    Info* tempInfo = temp->headInfoList;
    while(tempInfo != nullptr){
        if (tempInfo->name == infoName){
            //cout << "outputting true in CheckInfo " << endl;
            return true;
        }
        tempInfo = tempInfo->next;

    }

    //cout << "outputting false in CheckInfo " << endl;
    return false;


}

Contact* ContactList::searchContact(std::string first,std::string last){
    Contact* temp = headContactList;
    while(temp->first !=first && temp->last != last){
            temp = temp->next;
            //cout << "in traversal" << endl;
        }
    return temp;
}

// add info to the back of a contact's info list
// 1. return false and do nothing if the contact is not in the list
// 2. if the infoName is already in the info list, update the infoValue and return true
// 3. otherwise add the info to the back of the contact's list and return true
bool ContactList::addInfo(std::string first, std::string last, std::string infoName, std::string infoVal) {
    //cout << "in very beginning addInfo" << endl;
    Info* toAdd = new Info;
    toAdd->name = infoName;
    toAdd->value = infoVal;
    toAdd->next = nullptr;
    //cout << "in addInfo" << endl;
    if (headContactList == nullptr){
            return false;
        }

    if (checkListFL(first,last)==false)return false;
    else{
        Contact* temp = searchContact(first,last);
        if (temp->headInfoList==nullptr){
            temp->headInfoList=toAdd;
            return true;
        }
        else if(checkInfo(infoName, first,last)== true){
            Info* tempInfo = temp->headInfoList;
            while (tempInfo->next !=nullptr){
                if (tempInfo->name == infoName) break;
                tempInfo = tempInfo->next;

            }
            tempInfo->value = infoVal;
            //cout << "adding info for (case 2) "<< temp->first << endl;
            return true;
        }
        else{
            Info* tempInfo = temp->headInfoList;
            while (tempInfo->next !=nullptr){
                if (tempInfo->name == infoName) break;
                tempInfo = tempInfo->next;

            }
            //cout << "adding info for "<< temp->first << endl;
            tempInfo->next = toAdd;
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
    Contact* newContact = new Contact;
    newContact->first = first;
    newContact->last = last;
    newContact->next = nullptr;
    newContact->headInfoList = nullptr;
    if (headContactList == nullptr){
        headContactList = newContact;
        this->count++;
        return true;
    }
    else if (checkListFL(first,last)==true) return false;
    else{
            if (compareContact(newContact,headContactList) == true){
                newContact->next = headContactList;
                headContactList = newContact;
                this->count++;
                return true;

            }
            Contact* temp = headContactList->next;
            Contact* previous = headContactList;
            while(temp!=nullptr){
                if (compareContact(newContact,temp) == true){
                    break;
                }
                previous = previous->next;
                temp = temp->next;
            }
            previous->next = newContact;
            newContact->next = temp;
            count++;
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

bool compareInfo(Info* newInfo,Info* temp){
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
    Info* newInfo = new Info;
    newInfo->name=infoName;
    newInfo->value=infoVal;
    newInfo->next=nullptr;
    
    if (headContactList == nullptr){
        return false;
    }
    Contact* tempContact = searchContact(first,last);
    cout << "created temp contact" << endl;
    if(checkListFL(first,last) == false)return false;
    cout << "past first if" << endl;
    if (tempContact->headInfoList==nullptr){
        tempContact->headInfoList=newInfo;
        return true;
    }
    else if(checkInfo(infoName, first,last)== true){
            cout << "past if statement" <<endl;
            Info* tempInfo = tempContact->headInfoList;
            cout << "made tempInfo" << endl;
            while (tempInfo !=nullptr){
                if (tempInfo->name == infoName) break;
                tempInfo = tempInfo->next;

            }
            tempInfo->value = infoVal;
            //cout << "adding info for (case 2) "<< temp->first << endl;
            return true;
            cout << "past first in if else if else if..." << endl;
        }
    
    else if (compareInfo(newInfo,tempContact->headInfoList)==true){
        newInfo->next=tempContact->headInfoList;
        tempContact->headInfoList=newInfo;
        return true;
    }
    else{
        Info* previous = tempContact->headInfoList;
        Info* tempInfo = tempContact->headInfoList->next;
        while (tempInfo != nullptr){
            if(compareInfo(newInfo,tempInfo)==true){
                break;
            }
            previous = previous->next;
            tempInfo = tempInfo->next;
        }
        previous->next=newInfo;
        newInfo->next=tempInfo;
        return true;
    }

}

// remove the contact and its info from the list
// 1. return false and do nothing if the contact is not in the list
// 2. otherwise return true and remove the contact and its info
// - do not forget to update count
bool ContactList::removeContact(std::string first, std::string last) {
    return true;
}

// remove the info from a contact's info list
// 1. return false and do nothing if the contact is not in the list
// 2. return false and do nothing if the info is not in the contact's info list
// 3. otherwise return true and remove the info from the contact's list
bool ContactList::removeInfo(std::string first, std::string last, std::string infoName) {
    return true;
}

// destroy the list by removing all contacts and their infos
ContactList::~ContactList() {

}

// deep copy the source list
// - do not forget to update count
ContactList::ContactList(const ContactList &src) {

}

// remove all contacts and their info then deep copy the source list
// - do not forget to update count
const ContactList &ContactList::operator=(const ContactList &src) {
    if (this != &src) {

    }
    return *this;
}
