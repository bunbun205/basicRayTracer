
#include "createImage.hxx"
#include "ray.hxx"


color rayColor(const ray &r) {

        vec3 unitDirection = normalize(r.direction());
        auto t = 0.5 * (unitDirection.y() + 1.0);
        return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.4, 0.7, 1.0);
}

int main() {

        const auto aspectRatio = 16.0 / 9.0;
        const int width = 1280;
        const int height = static_cast<int> (width / aspectRatio);
        const int samplePerPixel = 3;
        char *image = new char [width * height * samplePerPixel];

        auto vpHeight = 2.0;
        auto vpWidth = aspectRatio * vpHeight;
        auto focalLenght = 1.0;

        auto origin = point3(0, 0, 0);
        auto horizontal = vec3(vpWidth, 0, 0);
        auto vertical = vec3(0, vpHeight, 0);
        auto llc = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focalLenght);

        for(int j = height - 1; j >= 0; j--) {

                for(int i = 0; i < width * samplePerPixel; i += 3) {

                        auto u = double(i) / (width * samplePerPixel);
                        auto v = double(j) / (height);
                        ray r(origin, llc + u * horizontal + v * vertical - origin);

                        image[i + (width * samplePerPixel * (j))] = static_cast<char>((rayColor(r).x()) * 255.999);
                        image[i + 1 +(width * samplePerPixel * (j))] = static_cast<char>((rayColor(r).y()) * 255.999);
                        image[i + 2 + (width * samplePerPixel * (j))] = static_cast<char>((rayColor(r).z()) * 255.999);
                }
        }
        
        createImage(width, height, samplePerPixel, image);
}