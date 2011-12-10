////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

namespace NLS {
	class ChatBalloon {
	public:
		void Set(string msg, string type);
		void Draw(int32_t x, int32_t y);
		string type;
		vector<Text> text;
		Sprite arrow, c, e, n, ne, nw, s, se, sw, w;
	};
	inline void ChatBalloon::Set(string msg, string type) {
		text.clear();
		this->type = type;
		// Set ALL sprites!
		Node dataNode = WZ["UI"]["ChatBalloon"][type];
		arrow = dataNode["arrow"];
		c = dataNode["c"];
		e = dataNode["e"];
		n = dataNode["n"];
		w = dataNode["w"];
		s = dataNode["s"];
		ne = dataNode["ne"];
		nw = dataNode["nw"];
		sw = dataNode["sw"];
		se = dataNode["se"];

		uint32_t color = (uint32_t)(int32_t)dataNode["clr"];
		uint8_t r = color & 0xFF;
		uint8_t g = (color << 8) & 0xFF;
		uint8_t b = (color << 16) & 0xFF;
		//uint8_t a = (color << 24) & 0xFF;
		const int32_t maxchars = 15;
		for (auto i = 0; i < msg.length(); i += maxchars) {
			size_t characters = maxchars;
			if (msg.length() < i + characters) {
				characters = msg.length() - i;
			}
			Text txt;
			txt.Set(Text::Color(r, g, b/*, a*/) + u32(msg.substr(i, characters)), 12);
			text.push_back(txt);
		}
	}

	inline void ChatBalloon::Draw(int32_t x, int32_t y) {
		int32_t width = 0, height = 0;
		for (auto i = 0; i < text.size(); i++) {
			if (width < text[i].Width()) width = text[i].Width();
			height += text[i].Height();
		}
		// Draw topline
		int32_t left = x - width/2, right = left + width;
		int32_t top = y - height, bottom = y;

		if (right % n.data->width != 0) {
			right -= right % n.data->width;// fill the gap
		}
		left -= left % 5;

		nw.Draw(left, top);
		for (auto i = left; i < right; i += n.data->width) 
			n.Draw(i, top);
		ne.Draw(right, top);
		
		int32_t counter = top;
		for (auto i = 0; i < text.size(); i++) {
			w.Draw(left, counter);
			for (auto j = left; j < right; j += c.data->width) 
				c.Draw(j, counter);
			e.Draw(right, counter);
			text[i].Draw(x - text[i].Width()/2, counter);
			counter += text[i].Height();
		}
		
		sw.Draw(left, bottom);
		counter = 0;
		for (auto i = left; i < right; i += s.data->width) {
			counter++;
			if (counter == 2) {
				arrow.Draw(i, bottom);
				continue;
			}
			s.Draw(i, bottom);
		}
		se.Draw(right, bottom);
	}

}