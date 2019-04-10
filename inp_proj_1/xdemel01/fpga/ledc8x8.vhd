library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use IEEE.std_logic_unsigned.all;

entity ledc8x8 is

    port (
        ROW: out std_logic_vector(0 to 7);
        LED: out std_logic_vector(0 to 7);
        SMCLK: in std_logic;
        RESET: in std_logic
    );

end ledc8x8;

architecture main of ledc8x8 is
    signal output_mode: std_logic_vector (1 downto 0) := "00";
    signal counter: std_logic_vector (7 downto 0) := (others => '0');
    signal delay_count: std_logic_vector (20 downto 0) := (others => '0');
    signal divided_clock: std_logic := '0';
    signal row_output: std_logic_vector (7 downto 0) := "10000000";
    signal col_output: std_logic_vector (7 downto 0) := "11111111";
begin
    
    -- Rozdeli vstupni signal / 256
    clock_div: process(RESET, SMCLK)
    begin
        if RESET = '1' then
            counter <= "00000000";
        elsif rising_edge(SMCLK) then
            counter <= counter + '1';
            if counter = "11111111" then
                divided_clock <= '1';
            else
                divided_clock <= '0';
            end if;
        end if;
    end process clock_div;


    -- Orotuje bit, ktery aktivuje radek
    row_rotation: process(RESET, SMCLK)
    begin
        if RESET = '1' then
            row_output <= "10000000";
        elsif divided_clock = '1' and rising_edge(SMCLK) then
            row_output <= row_output(0) & row_output(7 downto 1);
        end if;
    end process row_rotation;


    -- Co 1/4 vteřiny změní hodnotu output_modu
    delay: process(output_mode, RESET, SMCLK)
    begin
        if RESET = '1' then
            delay_count <= "000000000000000000000";
        elsif rising_edge(SMCLK) then
            delay_count <= delay_count + '1';
            if delay_count = "111000010000000000000" then
                delay_count <= "000000000000000000000";
                output_mode <= output_mode + 1;
            end if;
        end if;
    end process delay;

    display: process(row_output, output_mode)
	begin
		if output_mode = "10" then
            
            case row_output is
				when "10000000" => col_output <= "00001111";
				when "01000000" => col_output <= "01110111";
				when "00100000" => col_output <= "01111011";
				when "00010000" => col_output <= "01111011";
				when "00001000" => col_output <= "01110111";
				when "00000100" => col_output <= "00001111";
				when "00000010" => col_output <= "11111111";
				when "00000001" => col_output <= "11111111";
				when others     => col_output <= "11111111";
            end case;

		elsif output_mode = "00" then
            
            case row_output is
                when "10000000" => col_output <= "00000011";
				when "01000000" => col_output <= "11111011";
				when "00100000" => col_output <= "11111011";
				when "00010000" => col_output <= "11111011";
				when "00001000" => col_output <= "01111011";
				when "00000100" => col_output <= "10000111";
				when "00000010" => col_output <= "11111111";
				when "00000001" => col_output <= "11111111";
				when others     => col_output <= "11111111";
            end case;

		else 
			col_output <= "11111111";
		end if;
	end process display;

    LED <= col_output;
    ROW <= row_output;

end main;
