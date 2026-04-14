#include "BC.h"
#include "json.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace tndm;
using json = nlohmann::json;

static std::unordered_map<std::string, BC> const bc_name_to_enum_mapping = {
    {"Dirichlet", BC::Dirichlet},
    {"Natural", BC::Natural},
    {"Fault", BC::Fault}};

static std::unordered_map<BC, std::vector<long int>> bc_enum_to_tags_mapping = {
    {BC::Natural, {static_cast<long int>(BC::Natural)}},
    {BC::Fault, {static_cast<long int>(BC::Fault)}},
    {BC::Dirichlet, {static_cast<long int>(BC::Dirichlet)}}};

std::unordered_map<BC, std::string> make_reverse_map() {
  std::unordered_map<BC, std::string> reverse;
  for (const auto &[name, bc] : bc_name_to_enum_mapping) {
    reverse[bc] = name;
  }
  return reverse;
}
void printBCEnumToTagsMapping() {

  static std::unordered_map<BC, std::string> bc_enum_to_name_mapping =
      make_reverse_map();
  for (const auto &pair : bc_enum_to_tags_mapping) {
    auto it = bc_enum_to_name_mapping.find(pair.first);

    std::string name =
        (it != bc_enum_to_name_mapping.end()) ? it->second : "Unknown";

    std::cout << "BC Enum: " << name << " (" << static_cast<int>(pair.first)
              << ") -> Tags after parsing: ";

    for (const auto &tag : pair.second) {
      std::cout << tag << " ";
    }
    std::cout << std::endl;
  }
}

int main() {
  std::ifstream f("example_tag_map.json");
  json data = json::parse(f);

  // Build ownership map from default tags
  std::unordered_map<long int, BC> tag_owner;
  for (const auto &[bc, tags] : bc_enum_to_tags_mapping) {
    for (const auto &tag : tags) {
      tag_owner[tag] = bc;
    }
  }

  static std::unordered_map<BC, std::string> bc_enum_to_name_mapping =
      make_reverse_map();

  for (auto &bcMap : data["boundary_mapping"].items()) {
    auto it = bc_name_to_enum_mapping.find(bcMap.key());
    if (it != bc_name_to_enum_mapping.end()) {
      auto bc = it->second;

      // Convert JSON array to vector<long int>
      std::vector<long int> newTags =
          bcMap.value().get<std::vector<long int>>();

      for (const auto &tag : newTags) {
        auto ownerIt = tag_owner.find(tag);
        if (ownerIt != tag_owner.end() && ownerIt->second != bc) {
          // Tag already claimed by a different BC — throw error and stop
          if (ownerIt != tag_owner.end() && ownerIt->second != bc) {
            std::cerr << "Error: conflicting tags, same tag value " << tag
                      << " cannot belong to both '"
                      << bc_enum_to_name_mapping[ownerIt->second] << "' and '"
                      << bcMap.key() << "'.\n";
            return 1;
          }
        } else {
          auto &vec = bc_enum_to_tags_mapping[bc];
          if (std::find(vec.begin(), vec.end(), tag) == vec.end()) {
            vec.push_back(tag);
            tag_owner[tag] = bc;
          }
        }
      }
    } else {
      std::cout << "BC is not supported by tandem yet: " << bcMap.key() << '\n';
    }
  }
  printBCEnumToTagsMapping();
  return 0;
}