
/*
    Siv.h
*/

#pragma once

#include <vector>

#define Vi Vi
namespace Vi {
    namespace siv {

        using ID = size_t;
        constexpr ID InvalidID = (size_t)std::numeric_limits<size_t>::max();

        template <typename type>
        class Vector {

            /* API */

        public:
            size_t size() {
                
            }

            ID add(const type& element) {
                
            }

            ID add(type&& element) noexcept {
                
            }

            ID remove(const ID) {
                
            }

            type& operator [] (const ID) {

            }

            /* Private */

        private:
            std::vector<size_t> data_index;
            std::vector<size_t> id;
            std::vector<type> data;
        };
    }
}

