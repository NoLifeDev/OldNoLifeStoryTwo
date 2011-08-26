///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////

namespace NLS {
	class Connection {
	public:
		sf::TcpSocket* socket;
		string name;
		//other crap
		Connection(sf::TcpSocket*);
		~Connection();
	};
	extern set<Connection*> Connections;
};