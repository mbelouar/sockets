# colors
RED = \033[0;31m
GREEN = \033[0;32m
RESET = \033[0m

CC = gcc
RM = rm -rf
CLIENT = client.c
SERVER = server.c

all: server client
	@printf "\t    ______                       __                    __\n"	# Add a tab before each printf command
	@printf "\t   /      \                     /  |                  /  |  \n"
	@printf "\t  /######  |  ______    _______ ## |   __   ______   _## |_    _______\n"
	@printf "\t  ## \__##/  /      \  /       |## |  /  | /      \ / ##   |  /       |\n"
	@printf "\t  ##      \ /######  |/#######/ ## |_/##/ /######  |######/  /#######/ \n"
	@printf "\t   ######  |## |  ## |## |      ##   ##<  ##    ## |  ## | __##      \ \n"
	@printf "\t  /  \__## |## \__## |## \_____ ######  \ ########/   ## |/  |######  | \n"
	@printf "\t  ##    ##/ ##    ##/ ##       |## | ##  |##       |  ##  ##//     ##/  \n"
	@printf "\t   ######/   ######/   #######/ ##/   ##/  #######/    ####/ #######/ \n"
	@printf "\t｡☆✼★━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━★✼☆｡\n"
	@printf "\n\tBy:     BEL OUARRAQ MOHAMMED\n"
	@printf "\n\t        ET-TASS AYOUB\n"
	@printf "\n\t        AKOUBRI AYOUB\n"
	@printf "\n\t        EL KHARRAZ SAAD\n"
	@printf "\n\tLETS HAVE A SMALL COMMUNICATION SERVER CLIENT\n\n"

server: $(SERVER)
	@echo "$(RED)Compiling server ...$(RESET)"
	@$(CC) $(CFLAGS) $< -o $@
	@echo "$(GREEN)Compiling complete$(RESET)"

client: $(CLIENT)
	@echo "$(RED)Compiling client ...$(RESET)"
	@$(CC) $(CFLAGS) $< -o $@
	@echo "$(GREEN)Compiling complete$(RESET)"

clean:
	@$(RM) server client

re: clean all
