#include "game.h"

int main(void)
{
	struct Game game_context;

	if(game_init(&game_context) != 0) {
		fprintf(stderr, "Error: init failed!\n");
		return 1;
	}

	while(!game_should_end(&game_context)) {
		game_update(&game_context);
		
		game_draw(&game_context);
	}

	game_uninit(&game_context);
	
	return 0;
}
