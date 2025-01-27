// Copyright (C) 2022 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#include <string>

#include "json_object.h"
#include "primitive_type_base.h"
#include "reverse_inst.h"

namespace cldnn {
primitive_type_id reverse::type_id() {
    static primitive_type_base<reverse> instance;
    return &instance;
}

layout reverse_inst::calc_output_layout(reverse_node const& node) {
    return node.input(0).get_output_layout();
}

std::string reverse_inst::to_string(reverse_node const& node) {
    const auto prim = node.get_primitive();

    std::stringstream primitive_description;

    json_composite info;
    info.add("input id", node.input(0).id());
    info.add("axes id", node.input(1).id());
    const auto mode = prim->mode == reverse_mode::index ? "index" : "mask";
    info.add("mode", mode);

    auto node_info = node.desc_to_json();
    node_info->add("reverse_info", info);
    node_info->dump(primitive_description);

    return primitive_description.str();
}

reverse_inst::typed_primitive_inst(network& network, reverse_node const& node) : parent(network, node) {}

}  // namespace cldnn
