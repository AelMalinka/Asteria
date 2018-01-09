/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_OBJECT_INC
#	define ENTROPY_ASTERIA_OBJECT_INC

#	include <vector>
#	include <memory>
#	include <initializer_list>

#	include "../Character/Item.hh"

	namespace Entropy
	{
		namespace Asteria
		{
			class Object
			{
				public:
					Object();
					Object(std::initializer_list<std::shared_ptr<Item>>);
					Object(const Object &);
					Object(Object &&);
					~Object();
					std::size_t size() const;
					std::vector<std::shared_ptr<Item>>::iterator begin();
					std::vector<std::shared_ptr<Item>>::iterator end();
				private:
					std::vector<std::shared_ptr<Item>> _loot;
			};
		}
	}

#endif
