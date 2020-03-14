#include <nori/integrator.h>
#include <nori/scene.h>
#include <nori/warp.h>

NORI_NAMESPACE_BEGIN

class AoIntegrator : public Integrator {
public:
	AvIntegrator(const PropertyList &props) {
		m_length = (float)props.getFloat("length", 1);
	}

	Color3f Li(const Scene *scene, Sampler *sampler, const Ray3f &ray) const {
		Intersection its;
		if (!scene->rayIntersect(ray, its))
			return Color3f(1.0f);

		Ray3f m_ray(its.p, Warp::sampleUniformHemisphere(sampler, its.shFrame.n), Epsilon, m_length);
		if (!scene->rayIntersect(m_ray, its))
			return Color3f(1.0f);

		return Color3f(0.0f);
	}

	std::string toString() const {
		return "AvIntegrator[]";
	}
protected:
	float m_length;
};

NORI_REGISTER_CLASS(AvIntegrator, "ao");
NORI_NAMESPACE_END