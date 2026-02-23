CC = gcc
CFLAGS = -g

SHELL_EXEC = shell-ish
CUT_EXEC = cut
CHAT_EXEC = chatroom

all: $(SHELL_EXEC) $(CUT_EXEC) $(CHAT_EXEC)

$(SHELL_EXEC): shellish-skeleton.c
	$(CC) $(CFLAGS) -o $(SHELL_EXEC) shellish-skeleton.c

$(CUT_EXEC): $(CUT_EXEC).c
	$(CC) $(CFLAGS) -o $(CUT_EXEC) $(CUT_EXEC).c

$(CHAT_EXEC): $(CHAT_EXEC).c
	$(CC) $(CFLAGS) -o $(CHAT_EXEC) $(CHAT_EXEC).c

clean:
	rm -f $(SHELL_EXEC) $(CUT_EXEC) $(CHAT_EXEC)