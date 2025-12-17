#ifndef KYRAGAMEENGINE_SERIALIZATION_SERIALIZABLE_HPP
#define KYRAGAMEENGINE_SERIALIZATION_SERIALIZABLE_HPP

#include "BinaryWriter.hpp"
#include "BinaryReader.hpp"

namespace kyra {

	class Serializable {

	public:
		virtual ~Serializable() = default;


		virtual void write(BinaryWriter& writer) {

		}

		virtual void read(BinaryReader& reader) {

		}

	};

}

#endif