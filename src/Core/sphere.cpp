/*
    This file is part of Nori, a simple educational ray tracer

    Copyright (c) 2015 by Romain Prévost

    Nori is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License Version 3
    as published by the Free Software Foundation.

    Nori is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <nori/shape.h>
#include <nori/bsdf.h>
#include <nori/emitter.h>
#include <nori/warp.h>


NORI_NAMESPACE_BEGIN

class Sphere : public Shape {
public:
    Sphere(const PropertyList & propList) {
        m_position = propList.getPoint3("center", Point3f());
        m_radius = propList.getFloat("radius", 1.f);

        m_bbox.expandBy(m_position - Vector3f(m_radius));
        m_bbox.expandBy(m_position + Vector3f(m_radius));
    }

    virtual BoundingBox3f getBoundingBox(uint32_t index) const override { return m_bbox; }

    virtual Point3f getCentroid(uint32_t index) const override { return m_position; }

	virtual bool rayIntersect(uint32_t index, const Ray3f &ray, float &u, float &v, float &t) const override {

		/* to be implemented */

		Point3f C = m_position;
		Point3f O = ray.o;
		Vector3f D = ray.d;

		
		float a = pow(D.x(), 2) + pow(D.y(), 2) + pow(D.z(), 2);
		float b = 2 * (D.x() * (O.x() - C.x()) + D.y() * (O.y() - C.y()) + D.z() * (O.z() - C.z()));
		float c = pow(O.x() - C.x(), 2) + pow(O.y() - C.y(), 2) + pow(O.z() - C.z(), 2) - pow(m_radius, 2);

		float delta = pow(b,2) - 4 * a*c;

		if (delta > 0)
		{
			//a is positive so t1 is always the smaller value
			float t1 = (-b - sqrt(delta)) / 2 * a;
			float t2 = (-b + sqrt(delta)) / 2 * a;

			if (t1 > ray.mint && t1 < ray.maxt)
			{
				t = t1;
				return true;
			}

			if (t2 > ray.mint && t2 < ray.maxt)
			{
				t = t2;
				return true;
			}
		}

		return false;
	}

    virtual void setHitInformation(uint32_t index, const Ray3f &ray, Intersection & its) const override {
		its.p = ray.o + ray.d*its.t;
		its.geoFrame = its.shFrame = Frame((its.p - m_position).normalized());

		its.uv = sphericalCoordinates((its.p - m_position).normalized());
		its.uv[0] = (its.uv[0]) / (2 * M_PI);
		its.uv[1] /= M_PI;
	}

    virtual void sampleSurface(ShapeQueryRecord & sRec, const Point2f & sample) const override {
        Vector3f q = Warp::squareToUniformSphere(sample);
        sRec.p = m_position + m_radius * q;
        sRec.n = q;
        sRec.pdf = std::pow(1.f/m_radius,2) * Warp::squareToUniformSpherePdf(Vector3f(0.0f,0.0f,1.0f));
    }
    virtual float pdfSurface(const ShapeQueryRecord & sRec) const override {
        return std::pow(1.f/m_radius,2) * Warp::squareToUniformSpherePdf(Vector3f(0.0f,0.0f,1.0f));
    }


    virtual std::string toString() const override {
        return tfm::format(
                "Sphere[\n"
                "  center = %s,\n"
                "  radius = %f,\n"
                "  bsdf = %s,\n"
                "  emitter = %s\n"
                "]",
                m_position.toString(),
                m_radius,
                m_bsdf ? indent(m_bsdf->toString()) : std::string("null"),
                m_emitter ? indent(m_emitter->toString()) : std::string("null"));
    }

protected:
    Point3f m_position;
    float m_radius;
};

NORI_REGISTER_CLASS(Sphere, "sphere");
NORI_NAMESPACE_END
