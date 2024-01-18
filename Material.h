#ifndef MATERIAL_H
#define MATERIAL_H

class HitResult;

class ReflectResult
{
public:
    Ray m_ray;
    Vector3D m_color;
};

class Material
{
public:
    Vector3D m_color;
    virtual ReflectResult reflect(Ray& ray, HitResult& hit) = 0;
};


class Diffuse : public Material
{
public:
    Diffuse(const Vector3D& color)
    {
        m_color = color;
    };
    
    virtual ReflectResult reflect(Ray& ray, HitResult& hit) override
    {
        ReflectResult res;
        //TODO: 4. generate one scattered ray and assign it to res.m_ray
        // Generate a random direction on the hemisphere using Lambertian reflection
        Vector3D scatter_direction = hit.m_hitNormal + Vector3D::random_unit_vector();

        // Make sure the scatter direction is not aligned with the normal
        while (scatter_direction.dot(hit.m_hitNormal) <= 0)
        {
            scatter_direction = hit.m_hitNormal + Vector3D::random_unit_vector();
        }

        // Create the scattered ray starting from the hit point
        res.m_ray = Ray(hit.m_hitPos, scatter_direction);
        res.m_color = m_color;
        return res;
    }
};


class Specular : public Material
{
public:
    Specular(const Vector3D& color)
    {
        m_color = color;
    }
    
    virtual ReflectResult reflect(Ray& ray, HitResult& hit) override
    {
        ReflectResult res;
        //done: 5. generate one mirrored ray and assign it to res.m_ray

        // Calculate the reflection direction
        Vector3D incident_direction = ray.direction();
        Vector3D reflected_direction = incident_direction - 2 * dot(incident_direction, hit.m_hitNormal) * hit.m_hitNormal;

        // Create the reflected ray starting from the hit point
        res.m_ray = Ray(hit.m_hitPos, reflected_direction);
        //set the proper colour
        res.m_color = m_color;
        return res;
    }
};
#endif
