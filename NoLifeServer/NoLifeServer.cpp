////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"
unsigned short port = 10273;
int main(int argc, char **argv) {
#ifdef NLS_WINDOWS
	SetConsoleTitleA("NoLifeServer::Console");
#endif
	cout << "Loading NoLifeServer..." << endl;
	vector<string> strs(argv, argv+argc);
	
	sf::TcpSocket Client;
	sf::TcpListener Listener;

	while(true) {
		Listener.Listen(port);
		if(!Listener.Listen(port)) {
			cout << "Failed to listen on port 10273" << endl;
		}else {
			cout << "Waiting for connections on port 10273" << endl;
		}
		if(Listener.Accept(Client) != sf::TcpSocket::Done) {
			cout << "Client could not connect" << endl;
		} else {
			cout << "Client connected successfully" << endl;
			//Do something with client
		}
		/*if(Listener.IsBlocking() == true) {
			cout << "The socket is in blocking mode." << endl;
		}*/
	}
	NLS::Init(strs);
	while (NLS::Loop()) {}
	NLS::Unload();
	return 0;
}