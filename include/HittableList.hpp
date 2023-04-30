#ifndef HITTABLE_LIST_HPP
#define HITTABLE_LIST_HPP

#include "Hittable.hpp"

#include <memory>
#include <vector>

namespace rt
{
    class HittableList : public Hittable
    {
    public:
        /// \brief Default constructor
        HittableList() = default;

        /// \brief Constructor. 
        ///     Adds a Hittable object to the list of Hittable objects
        /// \param[in] object A shared pointer to a Hittable object
        explicit HittableList(std::shared_ptr<Hittable> object);

        /// \brief Erases the list of Hittable objects
        void clear();

        /// \brief Add an object to the list of Hittable objects
        /// \param[in] object A shared pointer to a Hittable object
        void add(std::shared_ptr<Hittable> object);

        /// \brief Determine if a ray hit an object
        bool hit(Ray const& ray, double tMin, double tMax, HitRecord& record) const noexcept override;

    private:
        std::vector<std::shared_ptr<Hittable>> m_objects;
    };
}

#endif