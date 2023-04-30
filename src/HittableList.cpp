#include "HittableList.hpp"

namespace rt
{
    HittableList::HittableList(std::shared_ptr<Hittable> object) : HittableList()
    {
        add(object);
    }

    void HittableList::clear()
    {
        m_objects.clear();
    }

    void HittableList::add(std::shared_ptr<Hittable> object)
    {
        m_objects.push_back(object);
    }

    bool HittableList::hit(Ray const& ray, double tMin, double tMax, HitRecord& record) const noexcept
    {
        HitRecord temp;
        bool hitAnything = false;
        auto closestSoFar = tMax;

        for (auto const& obj : m_objects) {
            if (obj->hit(ray, tMin, closestSoFar, temp)) {
                hitAnything = true;
                closestSoFar = temp.t;
                record = temp;
            }
        }

        return hitAnything;
    }
}