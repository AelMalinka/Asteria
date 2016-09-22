/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_EQUIPMENT_INC
#	define ENTROPY_ASTERIA_EQUIPMENT_INC

#	include "Item.hh"

	namespace Entropy
	{
		namespace Asteria
		{
			class Equipment :
				public Item
			{
				public:
					enum class Slot
					{
						Weapon,
						Armor,
						Accessory
					};
				public:
					Equipment(const std::string &, const Slot &, const Template &);
					Equipment(const Equipment &);
					Equipment(Equipment &&);
					virtual ~Equipment();
					const Slot &Where() const;
				private:
					Slot _where;
			};
		}
	}

#endif
