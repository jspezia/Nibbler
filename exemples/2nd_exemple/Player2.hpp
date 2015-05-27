
#ifndef PLAYER2_PP
# define PLAYER2_PP

# include "IEntity.hpp"
# include <iostream>

class Player2 : public IEntity
{
	private:
		std::string		_name;
		int				_score;
		Player2(void);

	public:
		Player2(std::string name);

		~Player2(void);

		std::string		getName(void) const;
		int				getScore(void) const;
		void			markPoint(void);
		void			announces(void) const;
};

extern "C"
{
	Player2		*createPlayer(const std::string &name);
	void		deletePlayer(Player2 *player);
}

#endif