import bpy
op = bpy.context.active_operator

op.filepath = 'D:\\Dev\\VulkanProjects\\HarvestHavoc\\libs\\velecs\\assets\\meshes\\equilateral_triangle.obj'
op.export_animation = False
op.start_frame = 1
op.end_frame = 250
op.forward_axis = 'Y'
op.up_axis = 'Z'
op.global_scale = 1.0
op.apply_modifiers = True
op.export_eval_mode = 'DAG_EVAL_VIEWPORT'
op.export_selected_objects = True
op.export_uv = False
op.export_normals = False
op.export_colors = False
op.export_materials = False
op.export_pbr_extensions = False
op.path_mode = 'AUTO'
op.export_triangulated_mesh = True
op.export_curves_as_nurbs = False
op.export_object_groups = False
op.export_material_groups = False
op.export_vertex_groups = False
op.export_smooth_groups = False
op.smooth_group_bitflags = False
