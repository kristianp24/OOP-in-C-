#include "UserInterface.h"
#include <iostream>
using namespace std;

int main() {
	
    UserInterface* user = new UserInterface();
	user->Menu();
	delete user;

}
