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
	Listener.SetBlocking(false);
	if(Listener.Listen(port) == sf::Socket::Status::Error) {
		cout << "Failed to listen on port 10273" << endl;
	} else {
		cout << "Waiting for connections on port 10273" << endl;
	}
	while(true) {
		if (Listener.Accept(Client) == sf::Socket::Error) {
			cout << "OH NOEZ" << endl;
		} else if (Listener.Accept(Client) == sf::Socket::Done) {
			cout << "Client connected successfully" << endl;
			//Do something with client
			// with it
		} else {
			//Who cares?
		}
	}
	NLS::Init(strs);
	while (NLS::Loop()) {}
	NLS::Unload();
	return 0;
}