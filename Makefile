CC = g++
CFLAGS = -Wall -Wextra -std=c++17

P1 = walsh
P2 = statistics
P3 = prinel
P4 = crypto

build:
	$(CC) $(CFLAGS) $(P1).cpp -o $(P1)
	$(CC) $(CFLAGS) $(P2).cpp -o $(P2)
	$(CC) $(CFLAGS) $(P3).cpp -o $(P3)
	$(CC) $(CFLAGS) $(P4).cpp -o $(P4)

run-p1:
	./$(P1)

run-p2:
	./$(P2)

run-p3:
	./$(P3)

run-p4:
	./$(P4)

clean:
	rm -rf $(P1) $(P2) $(P3) $(P4)
