/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_ITEM_INC
#	define ENTROPY_ASTERIA_ITEM_INC

#	include <Entropy/Hecate/Template.hh>

	namespace Entropy
	{
		namespace Asteria
		{
			class Character;
			using Template = Hecate::Template<Character>;

			class Item
			{
				public:
					Item(const std::string &, const Template &);
					Item(const Item &);
					Item(Item &&);
					virtual ~Item();
					const std::string &Name() const;
					Template &Value();
					const Template &Value() const;
				private:
					std::string _name;
					Template _templ;
			};
		}
	}

#endif
