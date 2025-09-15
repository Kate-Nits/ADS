// Copyright 2025 Ekaterina Ushnitskaya

#include <iostream>
#include <windows.h>
#include <cmath>

//#define EASY_EXAMPLE
//#define POSITION_OF_TWO_CIRCLE
#define POSITION_OF_TWO_SPHERE

//#define USER_INPUT

void set_color(int text_color, int bg_color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bg_color << 4) | text_color);
}

#ifdef EASY_EXAMPLE

#include <iostream>
#include <iomanip>
#include "../lib_easy_example/easy_example.h"

int main() {
  int a, b;
  float result;

  a = 1; b = 4;

  try {
      result = division(a, b);
      std::cout << a << " / " << b << " = "
          << std::setprecision(2) << result << std::endl;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }

  a = 1; b = 0;

  try {
      result = division(a, b);
      std::cout << a << " / " << b << " = "
          << std::setprecision(2) << result << std::endl;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }

  return 0;
}

#endif  // EASY_EXAMPLE

enum Location { intersecting, do_not_intersecting, tangent, inside, coinside };
//tangent - касающиеся, intersecting - пересекающиеся, inside - один в другом, coinside - совпадают
void print_result(const std::string& description, Location result) {
    std::cout << description << ": ";
    switch (result) {
    case coinside: std::cout << "COINCIDE"; break;
    case inside: std::cout << "INSIDE"; break;
    case tangent: std::cout << "TANGENT"; break;
    case intersecting: std::cout << "INTERSECTING"; break;
    case do_not_intersecting: std::cout << "DO_NOT_INTERSECT"; break;
    }
    std::cout << std::endl;
}

#ifdef POSITION_OF_TWO_CIRCLE
#include "../lib_circle/circle.h"

Location check_circle_position(const Circle& circle1, const Circle& circle2) {
    Point center1 = circle1.get_center();
    Point center2 = circle2.get_center();
    int radius1 = circle1.get_radius();
    int radius2 = circle2.get_radius();

    double distance = center1.distance_to(center2);
    int sum_rad = radius1 + radius2;
    int abs_difference = std::abs(radius1 - radius2);  // Исправлено: radius1 - radius2

    if (distance == 0 && radius1 == radius2) {
        return coinside;          // Окружности совпадают
    }
    else if (distance < abs_difference) {
        return inside;            // Одна окружность внутри другой
    }
    else if (distance == abs_difference) {
        return tangent;           // Внутреннее касание
    }
    else if (distance < sum_rad && distance > abs_difference) {
        return intersecting;      // Окружности пересекаются
    }
    else if (distance == sum_rad) {
        return tangent;           // Внешнее касание
    }
    else {
        return do_not_intersecting; // Окружности не пересекаются
    }
}

int main() {
    std::cout << "POSITION OF TWO CIRCLES" << std::endl;
    std::cout << "=======================================" << std::endl;

#ifdef USER_INPUT
    int value_dot1_ox, value_dot1_oy, value_radius1, value_dot2_ox, value_dot2_oy, value_radius2;
    std::cout << "Input center of the first circle: " << std::endl << "Input ox ";
    std::cin >> value_dot1_ox;
    std::cout << "Input oy ";
    std::cin >> value_dot1_oy;
    std::cout << "Input radius of the first circle: ";
    std::cin >> value_radius1;
    Circle circle1(Point(value_dot1_ox, value_dot1_oy), value_radius1);
    std::cout << "Input center of the second circle: " << std::endl << "Input ox ";
    std::cin >> value_dot2_ox;
    std::cout << "Input oy ";
    std::cin >> value_dot2_oy;
    std::cout << "Input radius of the second circle: ";
    std::cin >> value_radius2;
    Circle circle2(Point(value_dot2_ox, value_dot2_oy), value_radius2);
    Location result = check_circle_position(circle1, circle2);
    set_color(12, 0);
    std::cout << "RESULT:";
    set_color(7, 0);
    print_result(" ", result);
#else
    // 1 совпадающие окружности
    Circle circle1(Point(0, 0), 5);
    Circle circle2(Point(0, 0), 5);
    Location result1 = check_circle_position(circle1, circle2);
    print_result("1 Coincide circles (same center, same radius)", result1);

    // 2 одина окружность в другой
    Circle circle3(Point(0, 0), 10);
    Circle circle4(Point(1, 1), 2);
    Location result2 = check_circle_position(circle3, circle4);
    print_result("2 One circle inside another", result2);

    // 3 внутреннее касание
    Circle circle5(Point(0, 0), 5);
    Circle circle6(Point(3, 0), 2);
    Location result3 = check_circle_position(circle5, circle6);
    print_result("3 Internal tangent", result3);

    // 4 пересекающиеся окружности
    Circle circle7(Point(0, 0), 3);
    Circle circle8(Point(4, 0), 3);
    Location result4 = check_circle_position(circle7, circle8);
    print_result("4 Intersecting circles", result4);

    // 5 внешнее касание
    Circle circle9(Point(0, 0), 3);
    Circle circle10(Point(8, 0), 5);
    Location result5 = check_circle_position(circle9, circle10);
    print_result("5 External tangent", result5);

    // 6 непересекающиеся окружности
    Circle circle11(Point(0, 0), 2);
    Circle circle12(Point(10, 0), 3);
    Location result6 = check_circle_position(circle11, circle12);
    print_result("6 Non-intersecting circles", result6);
#endif // USER_INPUT
    std::cout << "=======================================" << std::endl;
    return 0;
}
#endif // POSITION_OF_TWO_CIRCLE

#ifdef POSITION_OF_TWO_SPHERE
#include "../lib_sphere/sphere.h"

Location check_sphere_position(const Sphere& sphere1, const Sphere& sphere2) {
    Point3D center1 = sphere1.get_center3D();
    Point3D center2 = sphere2.get_center3D();
    int radius1 = sphere1.get_radius();
    int radius2 = sphere2.get_radius();

    double distance = center1.distance_to(center2);
    int sum_rad = radius1 + radius2;
    int abs_difference = std::abs(radius1 - radius2);

    if (distance == 0 && radius1 == radius2) {
        return coinside;          // Сферы совпадают
    }
    else if (distance < abs_difference) {
        return inside;            // Одна сфера внутри другой
    }
    else if (distance == abs_difference) {
        return tangent;           // Внутреннее касание
    }
    else if (distance < sum_rad && distance > abs_difference) {
        return intersecting;      // Сферы пересекаются
    }
    else if (distance == sum_rad) {
        return tangent;           // Внешнее касание
    }
    else {
        return do_not_intersecting; // Сферы не пересекаются
    }
}
int main() {
    std::cout << "POSITION OF TWO SPHERE" << std::endl;
    std::cout << "=======================================" << std::endl;

#ifdef USER_INPUT
    int value_dot1_ox, value_dot1_oy, value_dot1_oz, value_radius1, value_dot2_ox, value_dot2_oy, value_dot2_oz, value_radius2;
    std::cout << "Input center of the first sphere: " << std::endl << "Input ox ";
    std::cin >> value_dot1_ox;
    std::cout << "Input oy ";
    std::cin >> value_dot1_oy;
    std::cout << "Input oz ";
    std::cin >> value_dot1_oz;
    std::cout << "Input radius of the first sphere: ";
    std::cin >> value_radius1;
    Sphere sphere1(Point3D(value_dot1_ox, value_dot1_oy, value_dot1_oz), value_radius1);
    std::cout << "Input center of the second sphere: " << std::endl << "Input ox ";
    std::cin >> value_dot2_ox;
    std::cout << "Input oy ";
    std::cin >> value_dot2_oy;
    std::cout << "Input oz ";
    std::cin >> value_dot2_oz;
    std::cout << "Input radius of the second sphere: ";
    std::cin >> value_radius2;
    Sphere sphere2(Point3D(value_dot2_ox, value_dot2_oy, value_dot2_oz), value_radius2);
    Location result = check_sphere_position(sphere1, sphere2);
    set_color(12, 0);
    std::cout << "RESULT:";
    set_color(7, 0);
    print_result(" ", result);
    std::cout << "=======================================" << std::endl;
#else
    // 1 совпадающие caths
    Sphere sphere1(Point3D(0, 0, 0), 5);
    Sphere sphere2(Point3D(0, 0, 0), 5);
    Location result7 = check_sphere_position(sphere1, sphere2);
    print_result("1 Coincide spheres (same center, same radius)", result7);

    // 2 одна сфера в другой
    Sphere sphere3(Point3D(0, 0, 0), 8);
    Sphere sphere4(Point3D(1, 1, 1), 2);
    Location result8 = check_sphere_position(sphere3, sphere4);
    print_result("2 One sphere inside another", result8);

    // 3 внутреннее касание сфер
    Sphere sphere5(Point3D(0, 0, 0), 5);
    Sphere sphere6(Point3D(3, 0, 0), 2);
    Location result9 = check_sphere_position(sphere5, sphere6);
    print_result("3 Internal tangent spheres", result9);

    // 4 пересекающиеся сферы
    Sphere sphere7(Point3D(0, 0, 0), 4);
    Sphere sphere8(Point3D(3, 0, 0), 3);
    Location result10 = check_sphere_position(sphere7, sphere8);
    print_result("4 Intersecting spheres", result10);

    // 5 внешнее касание
    Sphere sphere9(Point3D(0, 0, 0), 3);
    Sphere sphere10(Point3D(0, 8, 0), 5);
    Location result11 = check_sphere_position(sphere9, sphere10);
    print_result("5 External tangent spheres", result11);

    // 6 не пересекаются
    Sphere sphere11(Point3D(0, 0, 0), 2);
    Sphere sphere12(Point3D(0, 0, 15), 3);
    Location result12 = check_sphere_position(sphere11, sphere12);
    print_result("6 Non-intersecting spheres", result12);

    std::cout << "=======================================" << std::endl;
#endif // USER_INPUT

    return 0;
}

#endif // POSITION_OF_TWO_SPHERE
