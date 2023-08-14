CXX := gcc
OUT := program
LINK_FLAG := -pthread

APP_SRCS := $(wildcard ./*.c)
OBJ_FILES = $(APP_SRCS:.c=.o)

# Default target
all: $(OUT)

%.o: %.c
	$(CXX) $(LINK_FLAG) -c $< -o $@ -static

$(OUT): $(OBJ_FILES)
	$(CXX) $(LINK_FLAG) $(OBJ_FILES) -o $(OUT)

clean:
	rm -f $(OBJ_FILES) $(OUT)