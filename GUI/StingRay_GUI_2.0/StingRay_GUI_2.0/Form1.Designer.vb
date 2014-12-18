<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Venster1
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(Venster1))
        Me.gb_besturingspaneel = New System.Windows.Forms.GroupBox()
        Me.gb_variabelen = New System.Windows.Forms.GroupBox()
        Me.b_annuleren = New System.Windows.Forms.Button()
        Me.b_zend = New System.Windows.Forms.Button()
        Me.tb_radius = New System.Windows.Forms.TextBox()
        Me.l_radius = New System.Windows.Forms.Label()
        Me.tb_draaihoek = New System.Windows.Forms.TextBox()
        Me.l_draaihoek = New System.Windows.Forms.Label()
        Me.tb_snelheid = New System.Windows.Forms.TextBox()
        Me.l_snelheid = New System.Windows.Forms.Label()
        Me.tb_afstand = New System.Windows.Forms.TextBox()
        Me.l_afstand = New System.Windows.Forms.Label()
        Me.pb_signal3 = New System.Windows.Forms.PictureBox()
        Me.pb_signal2 = New System.Windows.Forms.PictureBox()
        Me.pb_signal1 = New System.Windows.Forms.PictureBox()
        Me.l_naam = New System.Windows.Forms.Label()
        Me.b_pingr = New System.Windows.Forms.Button()
        Me.l_copyrights = New System.Windows.Forms.Label()
        Me.b_pingm = New System.Windows.Forms.Button()
        Me.b_pingl = New System.Windows.Forms.Button()
        Me.b_right = New System.Windows.Forms.Button()
        Me.b_left = New System.Windows.Forms.Button()
        Me.b_backward = New System.Windows.Forms.Button()
        Me.b_forward = New System.Windows.Forms.Button()
        Me.b_rondas = New System.Windows.Forms.Button()
        Me.rtb_Terminal = New System.Windows.Forms.RichTextBox()
        Me.gb_Instellingen = New System.Windows.Forms.GroupBox()
        Me.b_refresh = New System.Windows.Forms.Button()
        Me.b_over = New System.Windows.Forms.Button()
        Me.b_sluit = New System.Windows.Forms.Button()
        Me.b_open = New System.Windows.Forms.Button()
        Me.cb_Baudrate = New System.Windows.Forms.ComboBox()
        Me.l_Baudrate = New System.Windows.Forms.Label()
        Me.cb_COMpoort = New System.Windows.Forms.ComboBox()
        Me.l_COMpoort = New System.Windows.Forms.Label()
        Me.SerialPort1 = New System.IO.Ports.SerialPort(Me.components)
        Me.b_stop = New System.Windows.Forms.Button()
        Me.gb_besturingspaneel.SuspendLayout()
        Me.gb_variabelen.SuspendLayout()
        CType(Me.pb_signal3, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.pb_signal2, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.pb_signal1, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.gb_Instellingen.SuspendLayout()
        Me.SuspendLayout()
        '
        'gb_besturingspaneel
        '
        Me.gb_besturingspaneel.Controls.Add(Me.b_stop)
        Me.gb_besturingspaneel.Controls.Add(Me.gb_variabelen)
        Me.gb_besturingspaneel.Controls.Add(Me.pb_signal3)
        Me.gb_besturingspaneel.Controls.Add(Me.pb_signal2)
        Me.gb_besturingspaneel.Controls.Add(Me.pb_signal1)
        Me.gb_besturingspaneel.Controls.Add(Me.l_naam)
        Me.gb_besturingspaneel.Controls.Add(Me.b_pingr)
        Me.gb_besturingspaneel.Controls.Add(Me.l_copyrights)
        Me.gb_besturingspaneel.Controls.Add(Me.b_pingm)
        Me.gb_besturingspaneel.Controls.Add(Me.b_pingl)
        Me.gb_besturingspaneel.Controls.Add(Me.b_right)
        Me.gb_besturingspaneel.Controls.Add(Me.b_left)
        Me.gb_besturingspaneel.Controls.Add(Me.b_backward)
        Me.gb_besturingspaneel.Controls.Add(Me.b_forward)
        Me.gb_besturingspaneel.Controls.Add(Me.b_rondas)
        Me.gb_besturingspaneel.Location = New System.Drawing.Point(12, 12)
        Me.gb_besturingspaneel.Name = "gb_besturingspaneel"
        Me.gb_besturingspaneel.Size = New System.Drawing.Size(418, 343)
        Me.gb_besturingspaneel.TabIndex = 0
        Me.gb_besturingspaneel.TabStop = False
        Me.gb_besturingspaneel.Text = "Besturingspaneel"
        '
        'gb_variabelen
        '
        Me.gb_variabelen.Controls.Add(Me.b_annuleren)
        Me.gb_variabelen.Controls.Add(Me.b_zend)
        Me.gb_variabelen.Controls.Add(Me.tb_radius)
        Me.gb_variabelen.Controls.Add(Me.l_radius)
        Me.gb_variabelen.Controls.Add(Me.tb_draaihoek)
        Me.gb_variabelen.Controls.Add(Me.l_draaihoek)
        Me.gb_variabelen.Controls.Add(Me.tb_snelheid)
        Me.gb_variabelen.Controls.Add(Me.l_snelheid)
        Me.gb_variabelen.Controls.Add(Me.tb_afstand)
        Me.gb_variabelen.Controls.Add(Me.l_afstand)
        Me.gb_variabelen.Location = New System.Drawing.Point(245, 82)
        Me.gb_variabelen.Name = "gb_variabelen"
        Me.gb_variabelen.Size = New System.Drawing.Size(163, 251)
        Me.gb_variabelen.TabIndex = 11
        Me.gb_variabelen.TabStop = False
        Me.gb_variabelen.Text = "Variabelen"
        '
        'b_annuleren
        '
        Me.b_annuleren.Location = New System.Drawing.Point(6, 213)
        Me.b_annuleren.Name = "b_annuleren"
        Me.b_annuleren.Size = New System.Drawing.Size(147, 23)
        Me.b_annuleren.TabIndex = 9
        Me.b_annuleren.Text = "Annuleren"
        Me.b_annuleren.UseVisualStyleBackColor = True
        '
        'b_zend
        '
        Me.b_zend.Location = New System.Drawing.Point(6, 184)
        Me.b_zend.Name = "b_zend"
        Me.b_zend.Size = New System.Drawing.Size(147, 23)
        Me.b_zend.TabIndex = 8
        Me.b_zend.Text = "Zenden"
        Me.b_zend.UseVisualStyleBackColor = True
        '
        'tb_radius
        '
        Me.tb_radius.Font = New System.Drawing.Font("Microsoft Sans Serif", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.tb_radius.ForeColor = System.Drawing.Color.DeepSkyBlue
        Me.tb_radius.Location = New System.Drawing.Point(6, 158)
        Me.tb_radius.Name = "tb_radius"
        Me.tb_radius.Size = New System.Drawing.Size(147, 20)
        Me.tb_radius.TabIndex = 7
        '
        'l_radius
        '
        Me.l_radius.AutoSize = True
        Me.l_radius.Location = New System.Drawing.Point(6, 142)
        Me.l_radius.Name = "l_radius"
        Me.l_radius.Size = New System.Drawing.Size(74, 13)
        Me.l_radius.TabIndex = 6
        Me.l_radius.Text = "Radius (in cm)"
        '
        'tb_draaihoek
        '
        Me.tb_draaihoek.Font = New System.Drawing.Font("Microsoft Sans Serif", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.tb_draaihoek.ForeColor = System.Drawing.Color.DeepSkyBlue
        Me.tb_draaihoek.Location = New System.Drawing.Point(6, 119)
        Me.tb_draaihoek.Name = "tb_draaihoek"
        Me.tb_draaihoek.Size = New System.Drawing.Size(147, 20)
        Me.tb_draaihoek.TabIndex = 5
        '
        'l_draaihoek
        '
        Me.l_draaihoek.AutoSize = True
        Me.l_draaihoek.Location = New System.Drawing.Point(6, 103)
        Me.l_draaihoek.Name = "l_draaihoek"
        Me.l_draaihoek.Size = New System.Drawing.Size(80, 13)
        Me.l_draaihoek.TabIndex = 4
        Me.l_draaihoek.Text = "Draaihoek (in °)"
        '
        'tb_snelheid
        '
        Me.tb_snelheid.Font = New System.Drawing.Font("Microsoft Sans Serif", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.tb_snelheid.ForeColor = System.Drawing.Color.DeepSkyBlue
        Me.tb_snelheid.Location = New System.Drawing.Point(6, 80)
        Me.tb_snelheid.Name = "tb_snelheid"
        Me.tb_snelheid.Size = New System.Drawing.Size(147, 20)
        Me.tb_snelheid.TabIndex = 3
        '
        'l_snelheid
        '
        Me.l_snelheid.AutoSize = True
        Me.l_snelheid.Location = New System.Drawing.Point(6, 64)
        Me.l_snelheid.Name = "l_snelheid"
        Me.l_snelheid.Size = New System.Drawing.Size(92, 13)
        Me.l_snelheid.TabIndex = 2
        Me.l_snelheid.Text = "Snelheid (in cm/s)"
        '
        'tb_afstand
        '
        Me.tb_afstand.Font = New System.Drawing.Font("Microsoft Sans Serif", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.tb_afstand.ForeColor = System.Drawing.Color.DeepSkyBlue
        Me.tb_afstand.Location = New System.Drawing.Point(6, 41)
        Me.tb_afstand.Name = "tb_afstand"
        Me.tb_afstand.Size = New System.Drawing.Size(147, 20)
        Me.tb_afstand.TabIndex = 1
        '
        'l_afstand
        '
        Me.l_afstand.AutoSize = True
        Me.l_afstand.Location = New System.Drawing.Point(6, 25)
        Me.l_afstand.Name = "l_afstand"
        Me.l_afstand.Size = New System.Drawing.Size(77, 13)
        Me.l_afstand.TabIndex = 0
        Me.l_afstand.Text = "Afstand (in cm)"
        '
        'pb_signal3
        '
        Me.pb_signal3.Image = CType(resources.GetObject("pb_signal3.Image"), System.Drawing.Image)
        Me.pb_signal3.Location = New System.Drawing.Point(180, 28)
        Me.pb_signal3.Name = "pb_signal3"
        Me.pb_signal3.Size = New System.Drawing.Size(48, 48)
        Me.pb_signal3.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize
        Me.pb_signal3.TabIndex = 10
        Me.pb_signal3.TabStop = False
        '
        'pb_signal2
        '
        Me.pb_signal2.Image = CType(resources.GetObject("pb_signal2.Image"), System.Drawing.Image)
        Me.pb_signal2.Location = New System.Drawing.Point(105, 28)
        Me.pb_signal2.Name = "pb_signal2"
        Me.pb_signal2.Size = New System.Drawing.Size(48, 48)
        Me.pb_signal2.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize
        Me.pb_signal2.TabIndex = 9
        Me.pb_signal2.TabStop = False
        '
        'pb_signal1
        '
        Me.pb_signal1.Image = CType(resources.GetObject("pb_signal1.Image"), System.Drawing.Image)
        Me.pb_signal1.Location = New System.Drawing.Point(29, 28)
        Me.pb_signal1.Name = "pb_signal1"
        Me.pb_signal1.Size = New System.Drawing.Size(48, 48)
        Me.pb_signal1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize
        Me.pb_signal1.TabIndex = 8
        Me.pb_signal1.TabStop = False
        '
        'l_naam
        '
        Me.l_naam.AutoSize = True
        Me.l_naam.Location = New System.Drawing.Point(311, 21)
        Me.l_naam.Name = "l_naam"
        Me.l_naam.Size = New System.Drawing.Size(87, 13)
        Me.l_naam.TabIndex = 8
        Me.l_naam.Text = "Jan Huijghebaert"
        '
        'b_pingr
        '
        Me.b_pingr.Location = New System.Drawing.Point(169, 82)
        Me.b_pingr.Name = "b_pingr"
        Me.b_pingr.Size = New System.Drawing.Size(70, 23)
        Me.b_pingr.TabIndex = 7
        Me.b_pingr.Text = "PING"
        Me.b_pingr.UseVisualStyleBackColor = True
        '
        'l_copyrights
        '
        Me.l_copyrights.AutoSize = True
        Me.l_copyrights.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.l_copyrights.Location = New System.Drawing.Point(291, 16)
        Me.l_copyrights.Name = "l_copyrights"
        Me.l_copyrights.Size = New System.Drawing.Size(20, 20)
        Me.l_copyrights.TabIndex = 7
        Me.l_copyrights.Text = "©"
        '
        'b_pingm
        '
        Me.b_pingm.Location = New System.Drawing.Point(93, 82)
        Me.b_pingm.Name = "b_pingm"
        Me.b_pingm.Size = New System.Drawing.Size(70, 23)
        Me.b_pingm.TabIndex = 6
        Me.b_pingm.Text = "PING"
        Me.b_pingm.UseVisualStyleBackColor = True
        '
        'b_pingl
        '
        Me.b_pingl.Location = New System.Drawing.Point(17, 82)
        Me.b_pingl.Name = "b_pingl"
        Me.b_pingl.Size = New System.Drawing.Size(70, 23)
        Me.b_pingl.TabIndex = 5
        Me.b_pingl.Text = "PING"
        Me.b_pingl.UseVisualStyleBackColor = True
        '
        'b_right
        '
        Me.b_right.Image = CType(resources.GetObject("b_right.Image"), System.Drawing.Image)
        Me.b_right.Location = New System.Drawing.Point(169, 187)
        Me.b_right.Name = "b_right"
        Me.b_right.Size = New System.Drawing.Size(70, 70)
        Me.b_right.TabIndex = 4
        Me.b_right.UseVisualStyleBackColor = True
        '
        'b_left
        '
        Me.b_left.Image = CType(resources.GetObject("b_left.Image"), System.Drawing.Image)
        Me.b_left.Location = New System.Drawing.Point(17, 187)
        Me.b_left.Name = "b_left"
        Me.b_left.Size = New System.Drawing.Size(70, 70)
        Me.b_left.TabIndex = 3
        Me.b_left.UseVisualStyleBackColor = True
        '
        'b_backward
        '
        Me.b_backward.Image = CType(resources.GetObject("b_backward.Image"), System.Drawing.Image)
        Me.b_backward.Location = New System.Drawing.Point(93, 263)
        Me.b_backward.Name = "b_backward"
        Me.b_backward.Size = New System.Drawing.Size(70, 70)
        Me.b_backward.TabIndex = 2
        Me.b_backward.UseVisualStyleBackColor = True
        '
        'b_forward
        '
        Me.b_forward.Image = CType(resources.GetObject("b_forward.Image"), System.Drawing.Image)
        Me.b_forward.Location = New System.Drawing.Point(93, 111)
        Me.b_forward.Name = "b_forward"
        Me.b_forward.Size = New System.Drawing.Size(70, 70)
        Me.b_forward.TabIndex = 1
        Me.b_forward.UseVisualStyleBackColor = True
        '
        'b_rondas
        '
        Me.b_rondas.Image = CType(resources.GetObject("b_rondas.Image"), System.Drawing.Image)
        Me.b_rondas.Location = New System.Drawing.Point(93, 187)
        Me.b_rondas.Name = "b_rondas"
        Me.b_rondas.Size = New System.Drawing.Size(70, 70)
        Me.b_rondas.TabIndex = 0
        Me.b_rondas.UseVisualStyleBackColor = True
        '
        'rtb_Terminal
        '
        Me.rtb_Terminal.BackColor = System.Drawing.Color.Black
        Me.rtb_Terminal.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.rtb_Terminal.Font = New System.Drawing.Font("Microsoft Sans Serif", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.rtb_Terminal.ForeColor = System.Drawing.Color.Aqua
        Me.rtb_Terminal.Location = New System.Drawing.Point(436, 190)
        Me.rtb_Terminal.Name = "rtb_Terminal"
        Me.rtb_Terminal.ReadOnly = True
        Me.rtb_Terminal.Size = New System.Drawing.Size(286, 165)
        Me.rtb_Terminal.TabIndex = 1
        Me.rtb_Terminal.Text = ""
        '
        'gb_Instellingen
        '
        Me.gb_Instellingen.Controls.Add(Me.b_refresh)
        Me.gb_Instellingen.Controls.Add(Me.b_over)
        Me.gb_Instellingen.Controls.Add(Me.b_sluit)
        Me.gb_Instellingen.Controls.Add(Me.b_open)
        Me.gb_Instellingen.Controls.Add(Me.cb_Baudrate)
        Me.gb_Instellingen.Controls.Add(Me.l_Baudrate)
        Me.gb_Instellingen.Controls.Add(Me.cb_COMpoort)
        Me.gb_Instellingen.Controls.Add(Me.l_COMpoort)
        Me.gb_Instellingen.Location = New System.Drawing.Point(436, 12)
        Me.gb_Instellingen.Name = "gb_Instellingen"
        Me.gb_Instellingen.Size = New System.Drawing.Size(286, 172)
        Me.gb_Instellingen.TabIndex = 2
        Me.gb_Instellingen.TabStop = False
        Me.gb_Instellingen.Text = "Instellingen"
        '
        'b_refresh
        '
        Me.b_refresh.Location = New System.Drawing.Point(200, 21)
        Me.b_refresh.Name = "b_refresh"
        Me.b_refresh.Size = New System.Drawing.Size(80, 27)
        Me.b_refresh.TabIndex = 0
        Me.b_refresh.Text = "Refresh"
        Me.b_refresh.UseVisualStyleBackColor = True
        '
        'b_over
        '
        Me.b_over.Location = New System.Drawing.Point(9, 140)
        Me.b_over.Name = "b_over"
        Me.b_over.Size = New System.Drawing.Size(271, 23)
        Me.b_over.TabIndex = 6
        Me.b_over.Text = "Info"
        Me.b_over.UseVisualStyleBackColor = True
        '
        'b_sluit
        '
        Me.b_sluit.Location = New System.Drawing.Point(9, 111)
        Me.b_sluit.Name = "b_sluit"
        Me.b_sluit.Size = New System.Drawing.Size(271, 23)
        Me.b_sluit.TabIndex = 5
        Me.b_sluit.Text = "Terminal sluiten"
        Me.b_sluit.UseVisualStyleBackColor = True
        '
        'b_open
        '
        Me.b_open.Location = New System.Drawing.Point(9, 82)
        Me.b_open.Name = "b_open"
        Me.b_open.Size = New System.Drawing.Size(271, 23)
        Me.b_open.TabIndex = 4
        Me.b_open.Text = "Terminal openen"
        Me.b_open.UseVisualStyleBackColor = True
        '
        'cb_Baudrate
        '
        Me.cb_Baudrate.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cb_Baudrate.Font = New System.Drawing.Font("Microsoft Sans Serif", 8.25!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cb_Baudrate.FormattingEnabled = True
        Me.cb_Baudrate.Location = New System.Drawing.Point(73, 55)
        Me.cb_Baudrate.Name = "cb_Baudrate"
        Me.cb_Baudrate.Size = New System.Drawing.Size(207, 21)
        Me.cb_Baudrate.TabIndex = 3
        '
        'l_Baudrate
        '
        Me.l_Baudrate.AutoSize = True
        Me.l_Baudrate.Location = New System.Drawing.Point(6, 55)
        Me.l_Baudrate.Name = "l_Baudrate"
        Me.l_Baudrate.Size = New System.Drawing.Size(53, 13)
        Me.l_Baudrate.TabIndex = 2
        Me.l_Baudrate.Text = "Baudrate:"
        '
        'cb_COMpoort
        '
        Me.cb_COMpoort.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cb_COMpoort.FormattingEnabled = True
        Me.cb_COMpoort.Location = New System.Drawing.Point(73, 25)
        Me.cb_COMpoort.Name = "cb_COMpoort"
        Me.cb_COMpoort.Size = New System.Drawing.Size(121, 21)
        Me.cb_COMpoort.TabIndex = 1
        '
        'l_COMpoort
        '
        Me.l_COMpoort.AutoSize = True
        Me.l_COMpoort.Location = New System.Drawing.Point(6, 28)
        Me.l_COMpoort.Name = "l_COMpoort"
        Me.l_COMpoort.Size = New System.Drawing.Size(61, 13)
        Me.l_COMpoort.TabIndex = 0
        Me.l_COMpoort.Text = "COM-poort:"
        '
        'SerialPort1
        '
        '
        'b_stop
        '
        Me.b_stop.Image = CType(resources.GetObject("b_stop.Image"), System.Drawing.Image)
        Me.b_stop.Location = New System.Drawing.Point(169, 111)
        Me.b_stop.Name = "b_stop"
        Me.b_stop.Size = New System.Drawing.Size(70, 70)
        Me.b_stop.TabIndex = 12
        Me.b_stop.UseVisualStyleBackColor = True
        '
        'Venster1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(732, 364)
        Me.Controls.Add(Me.gb_Instellingen)
        Me.Controls.Add(Me.rtb_Terminal)
        Me.Controls.Add(Me.gb_besturingspaneel)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.MaximizeBox = False
        Me.Name = "Venster1"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
        Me.Text = "StingRay Robot GUI Besturing"
        Me.gb_besturingspaneel.ResumeLayout(False)
        Me.gb_besturingspaneel.PerformLayout()
        Me.gb_variabelen.ResumeLayout(False)
        Me.gb_variabelen.PerformLayout()
        CType(Me.pb_signal3, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.pb_signal2, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.pb_signal1, System.ComponentModel.ISupportInitialize).EndInit()
        Me.gb_Instellingen.ResumeLayout(False)
        Me.gb_Instellingen.PerformLayout()
        Me.ResumeLayout(False)

    End Sub
    Friend WithEvents gb_besturingspaneel As System.Windows.Forms.GroupBox
    Friend WithEvents rtb_Terminal As System.Windows.Forms.RichTextBox
    Friend WithEvents gb_Instellingen As System.Windows.Forms.GroupBox
    Friend WithEvents cb_Baudrate As System.Windows.Forms.ComboBox
    Friend WithEvents l_Baudrate As System.Windows.Forms.Label
    Friend WithEvents cb_COMpoort As System.Windows.Forms.ComboBox
    Friend WithEvents l_COMpoort As System.Windows.Forms.Label
    Friend WithEvents b_over As System.Windows.Forms.Button
    Friend WithEvents b_sluit As System.Windows.Forms.Button
    Friend WithEvents b_open As System.Windows.Forms.Button
    Friend WithEvents l_naam As System.Windows.Forms.Label
    Friend WithEvents l_copyrights As System.Windows.Forms.Label
    Friend WithEvents b_refresh As System.Windows.Forms.Button
    Friend WithEvents SerialPort1 As System.IO.Ports.SerialPort
    Friend WithEvents b_rondas As System.Windows.Forms.Button
    Friend WithEvents pb_signal3 As System.Windows.Forms.PictureBox
    Friend WithEvents pb_signal2 As System.Windows.Forms.PictureBox
    Friend WithEvents pb_signal1 As System.Windows.Forms.PictureBox
    Friend WithEvents b_pingr As System.Windows.Forms.Button
    Friend WithEvents b_pingm As System.Windows.Forms.Button
    Friend WithEvents b_pingl As System.Windows.Forms.Button
    Friend WithEvents b_right As System.Windows.Forms.Button
    Friend WithEvents b_left As System.Windows.Forms.Button
    Friend WithEvents b_backward As System.Windows.Forms.Button
    Friend WithEvents b_forward As System.Windows.Forms.Button
    Friend WithEvents gb_variabelen As System.Windows.Forms.GroupBox
    Friend WithEvents tb_radius As System.Windows.Forms.TextBox
    Friend WithEvents l_radius As System.Windows.Forms.Label
    Friend WithEvents tb_draaihoek As System.Windows.Forms.TextBox
    Friend WithEvents l_draaihoek As System.Windows.Forms.Label
    Friend WithEvents tb_snelheid As System.Windows.Forms.TextBox
    Friend WithEvents l_snelheid As System.Windows.Forms.Label
    Friend WithEvents tb_afstand As System.Windows.Forms.TextBox
    Friend WithEvents l_afstand As System.Windows.Forms.Label
    Friend WithEvents b_annuleren As System.Windows.Forms.Button
    Friend WithEvents b_zend As System.Windows.Forms.Button
    Friend WithEvents b_stop As System.Windows.Forms.Button

End Class
