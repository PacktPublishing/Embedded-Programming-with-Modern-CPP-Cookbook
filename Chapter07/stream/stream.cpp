#include <iostream>
#include <sstream>
#include <list>

struct Point {
  int x, y;
};

struct Paths {
  Point source;
  std::list<Point> destinations;
};

std::ostream& operator<<(std::ostream& o, const Point& p) {
  o << p.x << " " << p.y << " ";
  return o;
}

std::istream& operator>>(std::istream& is, Point& p) {
  is >> p.x;
  is >> p.y;
  return is;
}

std::ostream& operator<<(std::ostream& o, const Paths& paths) {
  o << paths.source << paths.destinations.size() << " ";
  for (const auto& x : paths.destinations) { 
    o << x;
  }
  return o;
}

std::istream& operator>>(std::istream& is, Paths& paths) {
  size_t size;
  is >> paths.source;
  is >> size;
  for (;size;size--) {
    Point tmp;
    is >> tmp;
    paths.destinations.push_back(tmp);
  }
  return is;
}


int main(int argc, char** argv) {
  Paths paths = {{0, 0}, {{1, 1}, {0, 1}, {1, 0}}};

  std::stringstream in;
  in << paths;
  std::string serialized = in.str();
  std::cout << "Serialized paths into the string: ["
            << serialized << "]" << std::endl;

  std::stringstream out(serialized);
  Paths paths2;
  out >> paths2; 
  std::cout << "Original: " << paths.destinations.size()
            << " destinations" << std::endl;
  std::cout << "Restored: " << paths2.destinations.size()
            << " destinations" << std::endl;
  return 0;
}
