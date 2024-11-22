int mouse_release(int button, int x, int y, t_mlx_data *data) {
    (void)x;
    (void)y;
    if (button == 1) data->mouse.is_left_pressed = 0;
    if (button == 3) data->mouse.is_right_pressed = 0;
    return 0;
}



int mouse_move(int x, int y, t_mlx_data *data) {
    if (data && (data->mouse.is_left_pressed || data->mouse.is_right_pressed)) {
        int dx = x - data->mouse.last_x;
        int dy = y - data->mouse.last_y;
        
        
        t_vector translation = get_world_space_translation(data, &data->scene->camera, dx, dy);
        
        // Apply translation to the selected object or camera
        if (data->mouse.is_left_pressed)
            transform_scene(data->scene, (t_vector){0, 0, 0}, translation, (t_color){0, 0, 0});
        data->redraw_needed = 1;
    }
    
    data->mouse.last_x = x;
    data->mouse.last_y = y;
    return 0;
}
