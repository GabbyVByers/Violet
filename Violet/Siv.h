
/*
    Siv.h
*/

#pragma once

#include <vector>
#include <limits>
#include <algorithm>
#include <cassert>

#define Vi Vi
namespace Vi {
    namespace siv {

        using ID = size_t;
        constexpr ID InvalidID = (size_t)std::numeric_limits<size_t>::max();

        template <typename type>
        class Vector {

            /* API */

        public:
            ID validate_id(const ID element_id) {
                if (is_valid_id(element_id))
                    return element_id;
                return InvalidID;
            }

            size_t size() {
                return data.size();
            }

            ID add(const type& element) {
                /* size of id_from_index (and index_from_id) will be larger than size of data, if previous deletions have free'd up some ids */
                /* in this case, we want the newly added element to take on the id of the most rescently freed index */
                if (id_from_index.size() > data.size()) {
                    data.push_back(element);
                    size_t element_index = data.size() - 1;
                    ID element_id = id_from_index[element_index];
                    return element_id;
                }
                data.push_back(element);
                size_t prev_data_size = data.size() - 1;
                index_from_id.push_back(prev_data_size);
                id_from_index.push_back(prev_data_size);
                return prev_data_size;
            }

            ID add(type&& element) { /* not marked noexcept because std::vector::push_back() can throw */
                if (id_from_index.size() > data.size()) {
                    data.push_back(std::move(element));
                    size_t element_index = data.size() - 1;
                    ID element_id = id_from_index[element_index];
                    return element_id;
                }
                data.push_back(std::move(element));
                size_t prev_data_size = data.size() - 1;
                index_from_id.push_back(prev_data_size);
                id_from_index.push_back(prev_data_size);
                return prev_data_size;
            }

            ID remove(const ID element_id) {
                if (!is_valid_id(element_id))
                    return InvalidID;

                size_t last_index = data.size() - 1;
                size_t element_index = index_from_id[element_id];

                if (element_index == last_index) {
                    data.pop_back();
                    return element_id;
                }

                std::swap(data[element_index], data[last_index]);
                std::swap(id_from_index[element_index], id_from_index[last_index]);
                std::swap(index_from_id[id_from_index[element_index]], index_from_id[id_from_index[last_index]]);

                data.pop_back();
                return element_id;
            }

            type& at_index_unsafe(const size_t element_index) {
                return data[element_index];
            }

            type& operator [] (const ID element_id) {
                if (!is_valid_id(element_id)) {
                    Log::error("Invalid ID: " + std::to_string(element_id));
                    std::terminate();
                }
                size_t element_index = index_from_id[element_id];
                return data[element_index];
            }

            /* Allow Itterators (even works with <algorithm>, becuaase underlying container is an std::vector) */

            auto begin() { return data.begin(); }
            auto end()   { return data.end(); }

            auto begin() const { return data.begin(); }
            auto end()   const { return data.end(); }

            /* Private */

        private:
            std::vector<size_t> index_from_id;
            std::vector<size_t> id_from_index;
            std::vector<type> data;

            bool is_valid_id(const ID element_id) {
                if (element_id >= index_from_id.size())
                    return false;
                size_t element_index = index_from_id[element_id];
                if (element_index >= data.size())
                    return false;
                return true;
            }
        };
    }
}

