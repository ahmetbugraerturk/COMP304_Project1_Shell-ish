CC = gcc
CFLAGS = -g

SHELL_EXEC = shell-ish
CUT_EXEC = cut
CHAT_EXEC = chatroom
HANGMAN_EXEC = hangman

all: $(SHELL_EXEC) $(CUT_EXEC) $(CHAT_EXEC) $(HANGMAN_EXEC)

$(SHELL_EXEC): shellish-skeleton.c
	$(CC) $(CFLAGS) -o $(SHELL_EXEC) shellish-skeleton.c

$(CUT_EXEC): $(CUT_EXEC).c
	$(CC) $(CFLAGS) -o $(CUT_EXEC) $(CUT_EXEC).c

$(CHAT_EXEC): $(CHAT_EXEC).c
	$(CC) $(CFLAGS) -o $(CHAT_EXEC) $(CHAT_EXEC).c -lrt

$(HANGMAN_EXEC): $(HANGMAN_EXEC).c
	$(CC) $(CFLAGS) -o $(HANGMAN_EXEC) $(HANGMAN_EXEC).c -lrt

clean:
	rm -f $(SHELL_EXEC) $(CUT_EXEC) $(CHAT_EXEC) $(HANGMAN_EXEC)