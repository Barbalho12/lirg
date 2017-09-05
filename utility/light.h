#ifndef LIGHT_H
#define LIGHT_H

using namespace utility;


class DirectionLight{

	public:
		rgb m_intensity; 
		vec3 m_direction; 

     DirectionLight( rgb i = vec3(0,0,0), vec3 d = vec3(0,0,0) ){
     	m_intensity = i;
     	m_direction = d;
     }


     rgb intensity() const { 
     	return m_intensity;
     }
     vec3 direction() const {
     	return m_direction; 
     }

    virtual ~DirectionLight() { };
};

#endif /* LIGHT_H */