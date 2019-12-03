#ifndef HYPERTRIE_CARDINALITYESTIMATION_HPP
#define HYPERTRIE_CARDINALITYESTIMATION_HPP

#include <cmath>
#include "einsum/internal/Subscript.hpp"
#include "einsum/internal/Entry.hpp"

namespace einsum::internal {


	template<typename key_part_type, template<typename, typename> class map_type,
			template<typename> class set_type>
	struct CardinalityEstimation {
		using const_BoolHypertrie_t = const_BoolHypertrie<key_part_type, map_type, set_type>;

		/**
		 *
		 * @param operands
		 * @param label_candidates
		 * @param sc
		 * @return
		 */
		static Label getMinCardLabel(const std::vector<const_BoolHypertrie_t> &operands,
		                             const std::shared_ptr<Subscript> &sc,
		                             std::shared_ptr<Context> context) {
			const auto &label_set = sc->getOperandsLabelSet();
			for (const auto label : context->label_order) {
				if (label_set.count(label))
					return label;
			}
			throw std::logic_error{"The label ordering was not valid."};
		}
	};
}
#endif //HYPERTRIE_CARDINALITYESTIMATION_HPP
