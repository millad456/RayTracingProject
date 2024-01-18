#ifndef SPHERE_H
#define SPHERE_H

#include <memory>

using namespace std;
class Material;

class HitResult {
public:
    HitResult() { m_isHit = false; };
    bool m_isHit;
    Vector3D m_hitPos;
    Vector3D m_hitNormal;
    shared_ptr<Material> m_hitMaterial;
    float m_t;
};


class Sphere {
    
public:
    Sphere() {}
    Sphere(Vector3D center, float r, shared_ptr<Material> m)
    {
        m_center = center;
        m_radius = r;
        m_pMaterial = m;
    }
    HitResult hit(Ray& r, float min_t, float max_t);

    public:
    Vector3D m_center;
    float m_radius;
    shared_ptr<Material> m_pMaterial;
};


//test if ray hits this sphere within range min_t and max_t
HitResult Sphere::hit(Ray& ray, float min_t, float max_t)
{
    //done: 2. compute ray hit information on the sphere
    HitResult hit_result;
    hit_result.m_isHit = false;//by default its false

    // ccompute the vector from the ray's origin to the sphere's center
    Vector3D oc = ray.origin() - m_center;

    // coefficients for the quadratic equation. It's such a pain to type out normally
    float a = ray.direction().dot(ray.direction());
    float b = 2.0 * oc.dot(ray.direction());
    float c = oc.dot(oc) - m_radius * m_radius;

    // discriminant of the quadratic equation
    float discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
        // ray intersects the sphere, find the nearest intersection point
        float sqrt_discriminant = sqrt(discriminant);

        // check the two possible solutions for t, positive and negative
        float t1 = (-b - sqrt_discriminant) / (2.0 * a);
        float t2 = (-b + sqrt_discriminant) / (2.0 * a);

        // check if either solution is within the specified range
        if (t1 > min_t && t1 < max_t) {
            hit_result.m_isHit = true;
            hit_result.m_t = t1;
        } else if (t2 > min_t && t2 < max_t) {
            hit_result.m_isHit = true;
            hit_result.m_t = t2;
        }
    }

    // ff there's a hit, compute the hit position, normal, and material
    if (hit_result.m_isHit) {
        hit_result.m_hitPos = ray.at(hit_result.m_t);
        hit_result.m_hitNormal = (hit_result.m_hitPos - m_center) / m_radius;
        hit_result.m_hitMaterial = m_pMaterial;
    }//else return false bydefault

    return hit_result;
}

#endif
