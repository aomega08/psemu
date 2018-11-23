SRCS := $(shell find src -name "*.cpp")
OBJECTS := $(SRCS:.cpp=.o)
OUTPUT := out/psemu

CXXFLAGS := -std=c++17 -O3 -Wall -Wextra -Werror

all: $(OUTPUT)

$(OUTPUT): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) $< -c -o $@

clean:
	rm -f $(OBJECTS) $(OUTPUT)
