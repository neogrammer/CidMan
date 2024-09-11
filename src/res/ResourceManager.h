#ifndef RESOURCEMANAGER_H__
#define RESOURCEMANAGER_H__

#include <unordered_map> //unordered_map
#include <string> //string
#include <memory> //unique_ptr

//#include <stdexcept> //runtime_error
//#include <utility> //forward
//
//#include <SFML/Graphics/Font.hpp>
//#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio.hpp> //sf::Music

template<typename RESOURCE,typename IDENTIFIER = int>
struct ResourceManager
{
	ResourceManager() = default;

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;


    template<typename ... Args>
    void load(const IDENTIFIER& id, Args&& ... args);
    /*{
        std::unique_ptr<RESOURCE> ptr(new RESOURCE);
        if (not ptr->loadFromFile(std::forward<Args>(args)...))
            throw std::runtime_error("Impossible to load file");
        _map.emplace(id, std::move(ptr));
    };*/

    RESOURCE& get(const IDENTIFIER& id)const;
  /*  {
        return *_map.at(id);
    };*/

private:
    std::unordered_map<IDENTIFIER,std::unique_ptr<RESOURCE>> _map;
};

template<typename IDENTIFIER>
struct ResourceManager<sf::Music,IDENTIFIER>
{
	ResourceManager() = default;

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;


    template<typename ... Args>
    void load(const IDENTIFIER& id, Args&& ... args);
  /*  {
        std::unique_ptr<sf::Music> ptr(new sf::Music);

        if (not ptr->openFromFile(std::forward<Args>(args)...))
            throw std::runtime_error("Impossible to load file");
        _map.emplace(id, std::move(ptr));
    }*/

    sf::Music& get(const IDENTIFIER& id)const;
   /* {
        return *_map.at(id);
    };*/

private:
    std::unordered_map<IDENTIFIER,std::unique_ptr<sf::Music>> _map;
};
#include "tpl/ResourceManager.tpl"
#endif


//
//
//
//template<typename RESOURCE, typename IDENTIFIER>
//template<typename ... Args>
//void ResourceManager<RESOURCE, IDENTIFIER>::load(const IDENTIFIER& id, Args&& ... args)
//{
//    std::unique_ptr<RESOURCE> ptr(new RESOURCE);
//    if (not ptr->loadFromFile(std::forward<Args>(args)...))
//        throw std::runtime_error("Impossible to load file");
//    _map.emplace(id, std::move(ptr));
//}
//
//template<typename RESOURCE, typename IDENTIFIER>
//RESOURCE& ResourceManager<RESOURCE, IDENTIFIER>::get(const IDENTIFIER& id)const
//{
//    return *_map.at(id);
//}
//
////sf::Music special case
//template<typename IDENTIFIER>
//template<typename ... Args>
//void ResourceManager<sf::Music, IDENTIFIER>::load(const IDENTIFIER& id, Args&& ... args)
//{
//    std::unique_ptr<sf::Music> ptr(new sf::Music);
//
//    if (not ptr->openFromFile(std::forward<Args>(args)...))
//        throw std::runtime_error("Impossible to load file");
//    _map.emplace(id, std::move(ptr));
//};
//
//template<typename IDENTIFIER>
//sf::Music& ResourceManager<sf::Music, IDENTIFIER>::get(const IDENTIFIER& id) const
//{
//    return *_map.at(id);
//}
