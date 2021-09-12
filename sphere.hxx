#pragma once

#include "hittable.hxx"

class sphere : public hittable {

public:
        sphere() {}
        sphere(point3 cen, double r) : center(cen), radius(r) {}

        virtual bool hit(const ray &r, double tMin, double tMax, hitRecord &rec) const override;

public:
        point3 center;
        double radius;
};

bool sphere::hit(const ray &r, double tMin, double tMax, hitRecord &rec) const {

        vec3 oc = r.origin() - center;
        auto a = r.direction().lengthSquared();
        auto b = dot(oc, r.direction());
        auto c = oc.lengthSquared() - radius * radius;

        auto discriminant = b * b - a * c;

        if(discriminant < 0) return false;
        auto sqrtd = std::sqrt(discriminant);

        auto root = (-b - sqrtd) / a;
        if(root < tMin || root > tMax) {

                root = (-b + sqrtd) / a;
                
                if(root < tMin || root > tMax) return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 outwardNormal = (rec.p - center) / radius;
        rec.setFaceNormal(r, outwardNormal);

        return true;
}