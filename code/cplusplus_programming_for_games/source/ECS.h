#pragma once

#include <iostream>
#include <bitset>
#include <queue>
#include <array>
#include <assert.h> 
#include <vector>
#include <queue>  
#include <inttypes.h> 
#include <stdint.h>
#include <unordered_map>
#include <typeinfo> // get the typeid
#include <memory>

/*
* ASSERT.h
This macro is disabled if, at the moment of including <assert.h>, 
a macro with the name NDEBUG has already been defined. 
This allows for a coder to include as many assert calls as needed in a source code 
while debugging the program and then disable all of them for the production version by 
simply including a line like:

#define NDEBUG

at the beginning of the code, before the inclusion of <assert.h>.
*/


// type alias and define the size of the arrays leter on
// int32 4 byte signed -2,147,483,648 to 2,147,483,647  - 1000 
// std::uint32_t 4 byte unsigned 0 to 4,294,967,295
// 4,294,967,295 = 1111 1111 1111 1111 1111 1111 1111 1111
using Entity = std::uint32_t;
const Entity MAX_ENTITIES = 5000;

// type alias and define the size of the arrays leter on
//  length 8 bits
using ComponentType = std::uint8_t;
//
const ComponentType MAX_COMPONENTS = 32;


/*Bitset
A bitset stores bits (elements with only two possible values: 0 or 1, true or false, ...).

The class emulates an array of bool elements, but optimized for space allocation: generally, 
each element occupies only one bit (which, on most systems,
is eight times less than the smallest elemental type: char).

included at the start*/


//#define M 32
//bitset<M> bset1;
//
//// bset2 is initialized with bits of 20
//bitset<M> bset2(20);
//
//// bset3 is initialized with bits of specified binary string
//bitset<M> bset3(string("1100"));
//
//// cout prints exact bits representation of bitset
//cout << bset1 << endl; // 00000000000000000000000000000000
//cout << bset2 << endl; // 00000000000000000000000000010100
//cout << bset3 << endl; // 00000000000000000000000000001100
//cout << endl;

// const ComponentType MAX_COMPONENTS = 32;
using Signature = std::bitset <MAX_COMPONENTS>;

using Somethign = std::bitset <32>;



//int main() {
//
//	for (Entity myEnt = 0; myEnt < MAX_ENTITIES; myEnt++)
//	{
//		mAvailableEntities.push(myEnt);
//		std::cout << myEnt << std::endl;
//
//	}
//
//
//	return ;
//}

//component 
//if Transform has type 0, RigidBody has type 1, and Gravity has type 2, an entity that “has” those
//three components would have a signature of 0b111
struct Transform
{
	std::vector<float>* position = new std::vector<float>(2);
	std::vector<float>* scale = new std::vector<float>(2);
};

// The Entity Manager is in charge of distributing entity IDs and keeping record of which IDs 
// are in use and which are not.

class EntityManager
{
public:
	EntityManager() {

		// Initialize queue with all possible entity id
		for (Entity entity = 0; entity < MAX_ENTITIES; entity++) {
			mAvailableEntities.push(entity);
		}
	}

	Entity createEntity() {
		//assertion
		assert(mLivingEntityCount < MAX_ENTITIES && "Too many entities exist");
		
		// Take id from the queue
		Entity id = mAvailableEntities.front();
		mAvailableEntities.pop();
		++mLivingEntityCount;

		return id;
	}

	void DestroyEntity(Entity entity) {
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		// Invalidate the destroyed entity`s signature
		mSignatures[entity].reset();

		// Put the destoroyed ID at the back of the queue
		mAvailableEntities.push(entity);
		--mLivingEntityCount;
	}

private:
	// queue of unused entities ID`s
	std::queue<Entity> mAvailableEntities{};

	// Array of signatures where the index corresponds to the entity ID
	std::array<Signature, MAX_ENTITIES> mSignatures{};

	// Total living entities - used to keep limits on how many exists 
	uint32_t mLivingEntityCount{};
};

// The one instance of virtual inheritance in the entire implementation.
// An interface is needed so that the ComponentManager (seen later)
// can tell a generic ComponentArray that an entity has been destroyed
// and that it needs to update its array mappings.

class IComponentArray {
public:
	// can be overridden by derived classes 
	virtual ~IComponentArray() = default;
	virtual void EntityDestroyed(Entity entity) = 0;
}; 

template<typename T>
class ComponentArray : public IComponentArray {
public:
	void InsertData(Entity entity, T component) {
		assert(mEntityToIndexMap.find(entity) == mEntityToIndexMap.end() &&
			"Component added to same entity more than once.");
		
		// say newIndex = msize(3) 
		size_t newIndex = mSize; 
		// map the entity to index and viceversa 
		// map entity key to newIndex(3); 		
		mEntityToIndexMap[entity] = newIndex;
		// viceVersa
		mIndexToEntityMap[newIndex] = entity;
		// map in array index 3 the component; 
		mComponentArray[newIndex] = component;
			++mSize;
	}

	void RemoveData(Entity entity) {
		assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && 
			"Removing non-existent component.");

		// copy element at end into deleted element place to maintain density		
		size_t indexOfRemovedEntity = mEntityToIndexMap[entity];
		size_t indexOfLastElement = mSize - 1; 

		// if remove entity2 & array size is 3: array[2] = array[3]
		mComponentArray[indexOfRemovedEntity] = mComponentArray[indexOfLastElement];

		// Update map to point to moved spot
		Entity entityOfLastElement = mIndexToEntityMap[indexOfLastElement];
		mEntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
		mIndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

		mEntityToIndexMap.erase(entity);
		mIndexToEntituyMap.erase(indexOfLastElement);
		--mSize; 
	}

	T& GetData(Entity entity) {

		assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && 
			"Retrieving non-existent component.");

		return mComponentArray[mEntityToIndexMap[entity]];
	}

	void EntityDestroyed(Entity entity) override
	{
		if (mEntityToIndexMap.find[entity] != mEntityToIndexMap.end()) {
			// remove the entity component if exist
			RemoveData(entity);
		}
	}

private: 
	// the packed array of components of type <T>
	// set to specific max amount, matching the max nr of entities
	// so that each entity has a unique spot.
	std::array<T, MAX_ENTITIES> mComponentArray;

	// map from an entity id to the array index
	// <key :: value>
	std::unordered_map<Entity, size_t> mEntityToIndexMap;

	// map from an array index to an entity ID
	std::unordered_map<size_t, Entity> mIndexToEntituyMap;

	//total size of valid entries in the array
	//unsinged int (starts from 0) 
	size_t mSize;
};

//The virtual inheritance of IComponentArray is unfortunate but,
// unavoidable.We'll have a list of every ComponentArray (one per component type),
//and we need to notify all of them when an entity is destroyed so that
//it can remove the entity's data if it exists.
//The only way to keep a list of multiple templated types is to
//keep a list of their common interface so that we can call
//EntityDestroyed() on all of them.

//Component Manager, which is in charge of talking to all of the 
//different ComponentArrays when a component needs to be added or removed.

//Component Manager have a ComponentType variable that increments by one
//with every component type that is registered.

// Any time you add a new type of component to your gameand want to use it, 
//you will first need to call RegisterComponent.

// C++function that will return a pointer to a const char array 
//representation of a type T.That pointer(which is just an integer)
//can be used as a unique key into a map of ComponentTypes.

class ComponentManager {
public:
	template<typename T>
	void RegisterComponent() {
		const char* typeName = typeid(T).name();

		assert(mComponentTypes.find(typeName) == mComponentTypes.end() && 
			"Registering component type more than once.");

		// add comp to the type map 
		mComponentTypes.insert({ typeName, mNextComponentType });

		//	std::make_shared
		//  Allocates and constructs an object of type T passing args to its constructor, 
		//	and returns an object of type shared_ptr<T> that owns and stores a pointer to it
		//	(with a use count of 1).
		//	This function uses ::new to allocate storage for the object.

		// create comp array pointer to add it in the array map
		mComponentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });

		++mNextComponentType;
	}

	template<typename T>
	ComponentType GetComponentType() {

		const char* typeName = typeid(T).name();

		assert(mComponentTypes.find(typeName) != mComponentTypes.end() 
			&& "Component not registered before use.");
		return mComponentTypes[typeName];
	}

	template<typename T>
	void AddComponent(Entity entity, T component) {
		GetComponentArray<T>()->InsertData(entity, component);
	}

	template<typename T>
	void RemoveComponent(Entity entity) {
		GetComponentArray<T>()->RemoveData(entity);
	}

	template<typename T>
	T& GetComponent(Entity entity) {
		// get referance to a component from array for entity
		return GetComponentArray<T>()->GetData(entity);
	}

	void EntityDestroyed(Entity entity) {
		// Notify each comp array that entity was destroyed
		// If it has a comp for that entity it will also remove it
		for (auto const& pair : mComponentArrays) {
			auto const& component = pair.second;

			component->EntityDestroyed(entity);
		}
	}

private:
	// Map for the type string pointer to a component type
	std::unordered_map<const char*, ComponentType> mComponentTypes{};

	// Map for type string pointer to a component array
	std::unordered_map < const char*, std::shared_ptr<IComponentArray>> mComponentArrays{};
	
	// The component type to be assigned to the next registered component 
	//- starting at 0
	ComponentType mNextComponentType{};

	//Convince functions to get the statically casted pointer to the
	// ComponentArray of type T.

	template <typename T>
	std::shared_ptr<ComponentArray<T>> GetComponentArray() {
		/* typeid =  Refers to a std::type_info object representing the
		type type. If type is a reference type, the result refers to a 
		std::type_info object representing the referenced type.*/

		const char* typeName = typeid(T).name();
		assert(mComponentTypes.find(typeName) != mComponentTypes.end() && 
			"Component not registered before use.");

		// static_pointer_cast: Creates a new instance of std::shared_ptr whose stored pointer
		// is obtained from r's stored pointer using a cast expression.
		return std::static_pointer_cast<ComponentArray<T>>(mComponentArrays)[typeName]);
	}

};








