import bpy
import os

# Get the current .blend file's directory
blend_file_path = bpy.data.filepath
blend_file_directory = os.path.dirname(blend_file_path)

# Go up one directory level
parent_directory = os.path.dirname(blend_file_directory)

# Set the export file path
export_file_name = 'mesh.obj'
export_file_path = os.path.join(parent_directory, export_file_name)

op = bpy.context.active_operator
op.filepath = export_file_path
op.export_animation = False
op.start_frame = 1
op.end_frame = 250
op.forward_axis = 'NEGATIVE_Y'
op.up_axis = 'NEGATIVE_Z'
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
